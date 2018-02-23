/* VGA screen simple driver. this adapted from minix-2.0.0
 *
 * The 6845 video controller used by the IBM PC shares its video memory with
 * the CPU somewhere in the 0xB0000 memory bank.  To the 6845 this memory
 * consists of 16-bit words.  Each word has a character code in the low byte
 * and a so-called attribute byte in the high byte.  The CPU directly modifies
 * video memory to display characters, and sets two registers on the 6845 that
 * specify the video origin and the cursor position.  The video origin is the
 * place in video memory where the first character (upper left corner) can
 * be found.  Moving the origin is a fast way to scroll the screen.
 * The position of the cursor relative to the start of the video RAM can be derived 
 * from c _column and c _row , but it is faster to store it explicitly (in c _cur ). Tanenbaum.
 * see:
 *  Minix
 *  https://github.com/bhanderson/cpts460/blob/master/lab6/vid.c
 */
#include <console.h>
#include <io.h>
#include <libc.h>
#include <system.h>
#include <string.h>
#include <sched.h>
#include <wait.h>
#include <unistd.h>
#include <semaphore.h>

/* Definitions used by the console driver. */
#define MONO_BASE    0xB0000   /* base of mono video memory */
#define COLOR_BASE   0xB8000   /* base of color video memory */
#define MONO_SIZE     0x1000   /* 4K mono video memory */
#define COLOR_SIZE    0x4000   /* 16K color video memory */
#define EGA_SIZE      0x8000   /* EGA & VGA have at least 32K */
#define BLANK_COLOR   0x0700   /* determines cursor color on blank screen */
#define SCROLL_UP          0   /* scroll forward */
#define SCROLL_DOWN        1   /* scroll backward */
#define BLANK_MEM ((u16_t *) 0)   /* tells mem_vid_copy() to blank the screen */
#define CONS_RAM_WORDS    80   /* video ram buffer size */
#define MAX_ESC_PARMS      2   /* number of escape sequence params allowed */

/* VGA CRT controller chips. */
#define M_6845         0x3B4   /* port for 6845 mono */
#define C_6845         0x3D4   /* port for 6845 color */
#define EGA            0x3C4   /* port for EGA card, predecessor of VGA */
#define INDEX              0   /* 6845's index register */
#define DATA               1   /* 6845's data register */
#define VID_ORIGIN        12   /* 6845's origin register */
#define CURSOR            14   /* 6845's cursor register */

/* Beeper. */
#define BEEP_FREQ     0x0533   /* value to put into timer to set beep freq */
#define B_TIME             3   /* length of CTRL-G beep is ticks */

#define NR_CONS 4

#define SCR_WIDTH    	80	/* # characters on a line */
#define SCR_LINES    	25	/* # lines on the screen */
#define SCR_SIZE	(80*25)	/* # characters on the screen */

#define DEFAULT_ATTR  ((LIGHT_BLUE<<4 | WHITE) << 8)
#define ERASE_CHAR             (DEFAULT_ATTR | 0x00)

int video_port;		/* I/O port for accessing 6845 */
int vido_mask;
int softscroll = 0;

typedef struct tty {int a;/*todo*/} tty_t;

typedef struct console {
  tty_t* tty;            /*associated tty*/
  int row;               /*current line*/
  int col;               /*current column*/
  unsigned short cursor; /* offset in video RAM for cursor*/
  unsigned short attr;   /*attribute.8 low bits are zeroed*/
  unsigned short blank;  /*erase character*/
  long start;            /* start of video memory of this console */
  long origin;     	  /* offset in RAM where 6845 base points */
  int  size;             /* size of video memory */
  long limit;            /* limit of this console's video memory */
  unsigned short ramqueue[CONS_RAM_WORDS]; /* buffer for video RAM */
  char inqueue[128];     /*for cons read*/
  int  inidx;            /*in index*/
  task_t* p;             /*active process reading from this console*/
  semaphore_t sem;       /*semaphore protecting this console*/
} console_t;

console_t consoles[NR_CONS];
console_t *curcons; /*currently visible*/

#define pos(cons,row,col) (unsigned short *)(cons->start + cons->origin*2 + (row)*SCR_WIDTH*2 + (col)*2)
#define cpos(cons) (unsigned short *)(cons->start + cons->origin*2 + cons->row*SCR_WIDTH*2 + cons->col*2 )
#define cursor(cons) (cons->origin + cons->col + cons->row*SCR_WIDTH)

extern int enter, page_up, page_down, backspace; /*keyborad.c*/
void set_6845(unsigned short value, int reg);

void cons_clear(int tty)
{
  console_t *cons = &consoles[tty];
  memsetw ((short*)pos(cons,0,0), cons->blank, COLOR_SIZE);
  cons->col = cons->row = 0;
}

void cons_init()
{
  curcons = &consoles[0];
  curcons->start = COLOR_BASE; 
  curcons->origin = 0;
  curcons->cursor = 0; 
  curcons->col = curcons->row = 0;
  curcons->attr = DEFAULT_ATTR;
  curcons->blank = ERASE_CHAR;
  curcons->size = SCR_SIZE;
  curcons->inidx = 0;
  video_port = C_6845;
  vido_mask = COLOR_SIZE - 1;
  cons_clear (0);
  sem_init(&curcons->sem, 1);
}

void clear_line(console_t* cons, int nr)
{
  memsetw ((short*)pos(cons,nr,0), (short)cons->blank, SCR_WIDTH);
}

#define SCROLL_UP   0
#define SCROLL_DOWN 1
void scroll(console_t *cons, int direction)
{
  if (softscroll) {
  } 
  else {
    if (direction == SCROLL_UP)
      cons->origin += SCR_WIDTH;
    else if (direction == SCROLL_DOWN)
      cons->origin -= SCR_WIDTH;
  }
  if (cons->origin > (COLOR_SIZE - 1)) {
    //copy physicaly last screen on the top of video ram TODO
    cons->origin = 0;
  }
  if (cons == curcons) set_6845(cons->origin, VID_ORIGIN);
}

void update_cursor(console_t *cons)
{
  cons->cursor = cursor(cons);
  set_6845 (cons->cursor, CURSOR);
}

void flush (console_t *cons)
{
  int i;
  
  for (i=0; i < cons->col; i++) {
    *pos(cons,cons->row,i) = cons->ramqueue[i];
  }
}
    
void cons_putchar(register char c)
{
  if (c == '\n') {
    flush (curcons);
    curcons->col = 0;
    curcons->row++;
  } 
  else {  
    curcons->ramqueue[curcons->col] = curcons->attr | c;
    curcons->col++;
  }
  
  if (curcons->col >= SCR_WIDTH) {
    flush (curcons);
    curcons->row++;
    curcons->col = 0;
  }      
  if (curcons->row >= SCR_LINES) {
    scroll(curcons, SCROLL_UP);
    clear_line (curcons, SCR_LINES-1);
    curcons->row = SCR_LINES-1;
    curcons->col = 0;
  }
  update_cursor(curcons);
}

void cons_write(char *str)
{
  char* tmp = str;
  while (*tmp)
    cons_putchar(*(char *)tmp++);
  flush (curcons);
}

void cons_read(char *buf)
{
  down (&curcons->sem);
  curcons->p = current;
  sleep();
  strncpy (&curcons->inqueue[0], &buf[0], 128); /*copy str from kernel to userspace*/
  curcons->p = NULL;
  curcons->inidx = 0;
  up (&curcons->sem);
}

void cons_handler(char (*getc)(void))
{
  char c;
  if ((c=getc()) >= 0) {
    if (c == 0) /*Android keyboard trick*/
      c = ' ';
    curcons->inqueue[curcons->inidx++] = c;
    cons_putchar (c);
    flush (curcons);
  }
  else if (enter) {
    curcons->inqueue[curcons->inidx] = '\0';
    task_t* tsk = curcons->p;
    wakeup(tsk);
  }
  else if (page_up)
    scroll(curcons, SCROLL_UP);
  else if (page_down)
    scroll(curcons, SCROLL_DOWN);
  else if (backspace)
    cons_backspace();
}

void move_cursor_arrow(int arrow)
{
  switch (arrow) {  
  case UP_ARROW   : curcons->row--; break;  
  case DOWN_ARROW : curcons->row++; break;  
  case LEFT_ARROW : curcons->col--; break;  
  case RIGHT_ARROW: curcons->col++; break;
  default : break; 
  }
  update_cursor(curcons);  
}


void show_cursor()
{
  update_cursor(curcons);
}

void hide_cursor()
{
  //move_cursor(-1,-1);
}

void cons_backspace()
{
  if (curcons->col <= 2) 
    return; /*dont remove ps1*/
  curcons->col--;
  *cpos(curcons) = curcons->blank;
  //memcpy ((char *)addr(x+1,y), (char *)addr(x,y), (COLUMNS - x)*2);
  //memcpy (&cons_buf[x+1], &cons_buf[x], (COLUMNS - x));
  update_cursor(curcons);
}

/* in:
 *   reg: which register pair to set
 *   value : 16-bit value to set it to
 * Set a register pair inside the 6845.
 * Registers 12-13 tell the 6845 where in video ram to start(origin)
 * Registers 14-15 tell the 6845 where to put the cursor
 */
void set_6845(unsigned short value, int reg)
{
  outb(reg, video_port + INDEX); /*set the index register*/
  outb((value >> 8) & 0xff, video_port + DATA);  /*output high byte*/
  outb(reg + 1, video_port + INDEX);
  outb(value & 0xff, video_port + DATA);  /*output low byte*/
}









