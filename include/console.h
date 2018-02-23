#ifndef _CONSOLE_H
#define _CONSOLE_H

#define UP_ARROW 1   /* fleche haut*/
#define DOWN_ARROW 2
#define LEFT_ARROW 3
#define RIGHT_ARROW 4

#define NOPRINT  1

enum COLOR {BLACK=0x00, BLUE=0x01, GREEN=0x02, RED=0x04, LIGHT_GREY=0x07, LIGHT_BLUE=0x09, WHITE=0x0f};

void cons_init();
void cons_write(char *str);
void cons_read(char *buf);
void cons_putchar(char c);
void cons_handler(char (*getc)(void));
void cons_backspace();
void cons_clear(int tty);

/*move the cursor cursor up/down/left/right*/
void move_cursor_arrow(int arrow);


#endif
