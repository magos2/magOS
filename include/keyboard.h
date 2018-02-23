#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <types.h>

#define k(x) 0

#ifdef _KEY_MAP_
/*key mapping fo scan code 1 (QWERTY)*/ 
char keymap [] = {
  0, k(ESC), '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', k(BACKSPACE),  /*0x0..0x0E scan codes*/
  k(TAB),     'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',    k(ENTER),  /*0x0F..0x1C*/
  k(LCTL),     'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',             /*0x1D..0x29*/
  k(LSH), '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',              k(RSH),  /*0x2A..0x36*/
  '*',            k(LALT),    k(SPACE),            k(CAPS),               k(F1), k(F2), /*0x37..*/
  };

char sh_keymap [] = {
  k(ESC),'~', '!', '@', '#', '4', '5', '6', '7', '8', '9', '0', '-', '=', k(BACKSPACE), /*0x0..0x0E scan codes*/
  k(TAB),      'Q', 'W', 'E', 'R', 'T', 'Y', 'u', 'i', 'o', 'p', '[', ']',        '\\', /*0x0F..0x1C*/
  k(LCTL),      'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',       k(ENTER), /*0x1D..0x29*/
  k(LSH),        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',              k(RSH),  /*0x2A..0x36*/
  '*',            k(LALT),    k(SPACE),            k(CAPS),               k(F1), k(F2), /*0x37..*/
  };
#endif //_KEY_MAP

void keyboard_handler();
char kbgetc();

#endif
