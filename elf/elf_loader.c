/* Copyright 2016 @AR
 *
 * ELF loader
 * Docs
 * http://geezer.osdevbrasil.net/osd/exec/elf.txt 
 * http://man7.org/linux/man-pages/man5/elf.5.html
 * https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-73709
 */
#include <stdio.h>  //FILE
#include <stdlib.h> 

#include "elf_loader.h"
#include "elf32.h"

void* load_elf_binary (const char* filename)
{
  void* pout;
  size_t size;
  FILE* fin;
  
  
  fin = fopen(filename, "rb");
  if (!fin) {
    perror("opening file") ;
    exit (EXIT_FAILURE);
  }
  //get file length
  fseek (fin, 0, SEEK_END);
  size = ftell (fin);
  fseek (fin, 0, SEEK_SET);
  
  pout = malloc (size*sizeof(char));
  fread (pout, size, 1, fin);
  
  fclose(fin);
  return pout;
}

