/* Copyright 2016 @AR
 * 
 * this a simple driver for 8042 PS/2 controller.
 * the controller is connected to the cpu via the irq 1.
 *
 * see: http://wiki.osdev.org/"8042"_PS/2_Controller
 *    http://www.computer-engineering.org
 *    https://github.com/TacOS-team/tacos/wiki/Clavier
*/
#define _KEY_MAP_
#include <keyboard.h>
#include <io.h>
#include <kernel.h>
#include <console.h>

#define C(c)  (char)(c)

/*keybaord registers*/
#define KB_STATUS_PORT 0x64
#define KB_CMD_BUF     0x64
#define KB_IN_BUF      0x60
#define KB_OUT_BUF     0x60

/*keybaord commands*/
#define KB_ECHO  0xFE
#define KB_RESET 0xFF
#define KB_LED   0xED

/*status register bits*/
#define OUT_BUF_FULL 0x01
#define IN_BUF_FULL  0x02
#define SYS_FLAG     0x04

int left_shift = 0, right_shift = 0;
int caps = 0;
int left_ctrl = 0, right_ctrl = 0;
int fn = 0;
int left_alt = 0, right_alt = 0;
int alt_gr = 0;
int up_arrow = 0, down_arrow = 0, left_arrow = 0, right_arrow = 0;
int backspace = 0;
int enter = 0;
int page_up = 0, page_down = 0;
unsigned char prev_code = 0; /*treat E0 keys*/

char kbgetc()
{
  unsigned char code;
  char c;
  int cap;

  code = inb_p(KB_IN_BUF);
  
  if (prev_code == 0xE0) { /*Complexe codes: E0,1D*/
    switch (code) { 
    case 0x1D: right_ctrl = 1;  break;    
    case 0x38: right_alt = 1;   break;    
    case 0x48: up_arrow = 1;    break;
    case 0x49: page_up = 1;     break;
    case 0x4B: left_arrow = 1;  break;   
    case 0x4D: right_arrow = 1; break;     
    case 0x50: down_arrow = 1;  break;    
    case 0x51: page_down = 1;   break;    
    default:    break;
    }
    switch (code - 0x80) { /* Make Code */
    case 0x1D: right_ctrl = 0;  break;    
    case 0x38: right_alt = 0;   break;    
    case 0x48: up_arrow = 0;    break;
    case 0x49: page_up = 0;     break;
    case 0x4B: left_arrow = 0;  break;   
    case 0x4D: right_arrow = 0; break;     
    case 0x50: down_arrow = 0;  break;    
    case 0x51: page_down = 0;   break;    
    default:    break;
    }
    prev_code = 0;
  }
  else if (code <= 0x80)  /* code imprimable, key pressed*/
    switch (code) {
    case 0x0E: backspace = 1;   break;
    case 0x3A: caps = !caps;    break;    
    case 0x2A: left_shift = 1;  break;    
    case 0x36: right_shift = 1; break;    
    case 0x1D: left_ctrl = 1;   break;    
    case 0x38: left_alt = 1;    break;    
    case 0x1C: enter = 1;       break;
    default:   cap = (caps|left_shift|right_shift);
               if (!cap)
                 c = keymap[code];
               else
                 c = sh_keymap[code];
               return c;  
    }
  else if (code < 0xE0)  /* Break Code, key released */
    switch (code - 0x80) {
    case 0x0E: backspace = 0;   break;
    case 0x2A: left_shift = 0;  break;    
    case 0x36: right_shift = 0; break;    
    case 0x1D: left_ctrl = 0;   break;    
    case 0x38: left_alt = 0;    break;    
    case 0x1C: enter = 0;       break;  
    default:    break;    
    }
  else if (code == 0xE0)
    prev_code = 0xE0;
  return -NOPRINT;
}

void keyboard_handler()
{
  cons_handler(kbgetc);
}




