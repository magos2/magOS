/* Copyright 2017 @AR
 *
 * shellcode.S start a Linux shellcode.
 *
 * Compile:
 */    
 
 .att_syntax noprefix
 .code32
 
 .text

_start: 
  mov $shell, ebx 
 
 
 
 
shell:
  .ascii "/bin/sh0aaabbb"   # not asciz! chain must not be terminated by a null char