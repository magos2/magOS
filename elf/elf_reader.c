/* Copyright 2016 @AR
 *
 * ELF reader
 * Docs
 * http://geezer.osdevbrasil.net/osd/exec/elf.txt 
 * http://man7.org/linux/man-pages/man5/elf.5.html
 * https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblj/index.html#chapter6-73709
 */
#include <stdio.h>  //FILE
#include <stdlib.h> 
#include <string.h>

#include "elf_reader.h"
#include "elf_loader.h"
#include "elf32.h"

#define STR_CASE_0(id) case (id) : return &#id[0];
#define STR_CASE_1(id) case (id) : return &#id[1];
#define STR_CASE_2(id) case (id) : return &#id[2];
#define STR_CASE_3(id) case (id) : return &#id[3];
#define STR_CASE_4(id) case (id) : return &#id[4]; /* ex. STR_CASE_4 (SHT_SYMTAB) = case SHT_SYMTAB : return "SYMTAB" */

char* machine_class (Elf32_Ehdr* ehdr) {
  if (ehdr->e_ident[EI_CLASS] == ELFCLASS32 )
    return "32-bit";
  else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64 )
    return "64-bit";
  return "Unknown class";
} 

char* data_format (Elf32_Ehdr* ehdr) {
  if (ehdr->e_ident[EI_DATA] == ELFDATA2LSB )
    return "little-endian";
  else if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB )
    return "big-endian";
  return "Unknown";
}  

char* os_abi (Elf32_Ehdr* ehdr) {
  if (ehdr->e_ident[EI_OSABI] == ELFOSABI_SYSV )
    return "UNIX System V ABI";
  else if (ehdr->e_ident[EI_OSABI] == ELFOSABI_LINUX )
    return "GNU/Linux";
  else if (ehdr->e_ident[EI_OSABI] == ELFOSABI_ARM )
    return "ARM";
  return "Other";
}                  

char* e_type (Elf32_Ehdr* ehdr) {
  switch (ehdr->e_type) {
  case ET_NONE : return "Unknown type";
  case ET_REL :  return "Relocatable";
  case ET_EXEC : return "Executable";
  case ET_DYN :  return "Shared object";
  case ET_CORE : return "Core file";
  }
  return "Unknown";
}
char* e_machine (Elf32_Ehdr* ehdr) {
  switch (ehdr->e_machine) {
  case EM_NONE :  return "Unknown machine";
  case EM_M32 :   return "AT&T WE32100";
  case EM_SPARC : return "Sun SPARC";
  case EM_386 :   return "Intel i386";
  case EM_ARM :   return "ARM";
  }
  return "Other";
}

char* sh_type (Elf32_Shdr* shdr) {
  switch (shdr->sh_type) {
    STR_CASE_4 (SHT_NULL)
    STR_CASE_4 (SHT_PROGBITS)
    STR_CASE_4 (SHT_SYMTAB)
    STR_CASE_4 (SHT_STRTAB)
    STR_CASE_4 (SHT_RELA)
    STR_CASE_4 (SHT_HASH)
    STR_CASE_4 (SHT_DYNAMIC)
    STR_CASE_4 (SHT_NOTE)
    STR_CASE_4 (SHT_NOBITS)
    STR_CASE_4 (SHT_REL)
    STR_CASE_4 (SHT_SHLIB)
    STR_CASE_4 (SHT_DYNSYM)
    STR_CASE_4 (SHT_NUM)
    STR_CASE_4 (SHT_LOPROC)
    STR_CASE_4 (SHT_HIPROC)
    STR_CASE_4 (SHT_LOUSER)
    STR_CASE_4 (SHT_HIUSER)
  }
  return "Unknown";
}


char* sh_flags (Elf32_Word flags, char* buf) {
  int i = 0;
  if (flags & SHF_WRITE) 
    buf[i++] = 'W';
  if (flags & SHF_ALLOC) 
    buf[i++] = 'A';
  if (flags & SHF_EXECINSTR) 
    buf[i++] = 'X';
  if (flags & SHF_MASKPROC) 
    buf[i++] = 'p';
  buf[i] = '\0';
  return buf;
}

void key_to_flags() {
  printf ("Key to Flags :\n" \
          "    W (write), A (alloc), X (execute), M (merge), S (strings) \n" \
          "    I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n" \
          "    O (extra OS processing required) o (OS specific), p (processor specific)\n");
}
  
char* p_flags (Elf32_Word flags, char* buf) {
  int i = 0;
  if (flags & PF_R) 
    buf[i++] = 'R';
  if (flags & PF_W) 
    buf[i++] = 'W';
  if (flags & PF_X) 
    buf[i++] = 'X';
  buf[i] = '\0';
  return buf;
}

char* symbol_type_info (int st_info)
{
  switch (ELF32_ST_TYPE(st_info)) {
    STR_CASE_4 (STT_NOTYPE)
    STR_CASE_4 (STT_OBJECT)
    STR_CASE_4 (STT_FUNC)
    STR_CASE_4 (STT_SECTION)  
    STR_CASE_4 (STT_FILE)
    STR_CASE_4 (STT_LOPROC)
    STR_CASE_4 (STT_HIPROC)
  }
  return "Unknown";
}

char* symbol_bind_info (int st_info)
{
  switch (ELF32_ST_BIND(st_info)) {
    STR_CASE_4 (STB_LOCAL)
    STR_CASE_4 (STB_GLOBAL)
    STR_CASE_4 (STB_WEAK)
    STR_CASE_4 (STB_LOPROC)
    STR_CASE_4 (STB_HIPROC)
  }
  return "Unknown";
}

char* p_type (Elf32_Phdr* phdr) {
  switch (phdr->p_type) {
    STR_CASE_3 (PT_NULL)
    STR_CASE_3 (PT_LOAD)
    STR_CASE_3 (PT_DYNAMIC)
    STR_CASE_3 (PT_INTERP)
    STR_CASE_3 (PT_NOTE)
    STR_CASE_3 (PT_SHLIB)
    STR_CASE_3 (PT_PHDR)
    STR_CASE_3 (PT_TLS)
    STR_CASE_3 (PT_LOOS)
    STR_CASE_3 (PT_GNU_EH_FRAME)
    STR_CASE_3 (PT_GNU_STACK)
    STR_CASE_3 (PT_GNU_RELRO)
    STR_CASE_3 (PT_SUNWBSS)
    STR_CASE_3 (PT_SUNWSTACK)
    STR_CASE_3 (PT_HIOS)
    STR_CASE_3 (PT_LOPROC)
    STR_CASE_3 (PT_HIPROC)
    STR_CASE_3 (PT_ARM_EXIDX)
  }
  return "Unknown";
}

char* rel_type (Elf32_Word type )
{
  switch (type) {
    STR_CASE_0 (R_ARM_NONE)
    STR_CASE_0 (R_ARM_ABS32)
    STR_CASE_0 (R_ARM_REL32)
    STR_CASE_0 (R_ARM_PC13)
    STR_CASE_0 (R_ARM_ABS16)
    STR_CASE_0 (R_ARM_ABS12)
    STR_CASE_0 (R_ARM_THM_ABS5)
    STR_CASE_0 (R_ARM_ABS8)
    STR_CASE_0 (R_ARM_SBREL32)
    STR_CASE_0 (R_ARM_THM_CALL)
    STR_CASE_0 (R_ARM_THM_PC8)
    STR_CASE_0 (R_ARM_TLS_DESC)
    STR_CASE_0 (R_ARM_COPY)
    STR_CASE_0 (R_ARM_GLOB_DAT)
    STR_CASE_0 (R_ARM_JUMP_SLOT)
    STR_CASE_0 (R_ARM_RELATIVE)
    STR_CASE_0 (R_ARM_GOTOFF)
    STR_CASE_0 (R_ARM_GOTPC)
    STR_CASE_0 (R_ARM_GOT32)
    STR_CASE_0 (R_ARM_PLT32)
    STR_CASE_0 (R_ARM_CALL)
    STR_CASE_0 (R_ARM_JUMP24)
    STR_CASE_0 (R_ARM_THM_JUMP24)
    STR_CASE_0 (R_ARM_BASE_ABS)
    STR_CASE_0 (R_ARM_SBREL31)
    STR_CASE_0 (R_ARM_MOVW_ABS_NC)
    STR_CASE_0 (R_ARM_MOVT_ABS)
    STR_CASE_0 (R_ARM_MOVW_PREL_NC)
    STR_CASE_0 (R_ARM_MOVT_PREL)
    STR_CASE_0 (R_ARM_THM_MOVW_ABS_NC)
    STR_CASE_0 (R_ARM_THM_MOVT_ABS)
    STR_CASE_0 (R_ARM_GOT_ABS)
    STR_CASE_0 (R_ARM_GOT_PREL)
  }
  return "R_ARM_UND";
}

Elf32_Shdr* get_shdr_by_type (void* elf, Elf32_Word type)
{
  int i;
  Elf32_Ehdr* ehdr;
  Elf32_Shdr* shdr;
      
  ehdr = elf;
  
  for (i=0; i < ehdr->e_shnum; i++) {
    shdr = (Elf32_Shdr*)(elf + ehdr->e_shoff + (ehdr->e_shentsize) * i);
    if (shdr->sh_type == type) 
      return shdr;
  }
  return NULL;
}

/* type : sh_type to search
 * from : search from 'from' section header index in the section headers table
 */  
int get_shdr_id_by_type (void* elf, int from, Elf32_Word type)
{
  int i;
  Elf32_Ehdr* ehdr;
  Elf32_Shdr* shdr;
      
  ehdr = elf;
  
  for (i=from; i < ehdr->e_shnum; i++) {
    shdr = (Elf32_Shdr*)(elf + ehdr->e_shoff + (ehdr->e_shentsize) * i);
    if (shdr->sh_type == type) 
      return i;
  }
  return -1;
}

Elf32_Shdr* get_shdr_by_id (void* elf, int sh_id)
{
  Elf32_Ehdr* ehdr;
  ehdr = elf;
  
  return (Elf32_Shdr*)(elf + ehdr->e_shoff + (ehdr->e_shentsize) * sh_id);
}

char* resolve_section_name (void* elf, Elf32_Half sh_idx)
{
  Elf32_Ehdr* ehdr;
  Elf32_Shdr* shdr;
  
  switch (sh_idx) {
    STR_CASE_4 (SHN_UNDEF) // return "UNDEF"
    STR_CASE_4 (SHN_LOPROC)
    STR_CASE_4 (SHN_HIPROC)
    STR_CASE_4 (SHN_ABS)
    STR_CASE_4 (SHN_COMMON)
    STR_CASE_4 (SHN_HIRESERVE)
  }  
  // else we lookup the section name in .shstrtab
  
  ehdr = elf;
  shdr = (Elf32_Shdr*)(elf + ehdr->e_shoff);
  
  // section header string table .shstrtab
  Elf32_Shdr* sh_shstrtab = get_shdr_by_id (elf, ehdr->e_shstrndx);
  char* shstrtab = (char*)(elf + sh_shstrtab->sh_offset);
  
  return (shstrtab + shdr[sh_idx].sh_name);
  
}

char* resolve_symbol_name (void* elf,Elf32_Shdr* sh_symtab, Elf32_Word sym_name)
{
  // section string  table
  Elf32_Shdr* sh_strtab = get_shdr_by_id (elf, sh_symtab->sh_link);
  char* strtab = (char*)(elf + sh_strtab->sh_offset);
  
  return (strtab + sym_name);
  
}


void dump_elf_header (void* elf)
{
  Elf32_Ehdr* ehdr;
  
  ehdr = elf;
  
  printf ("ELF Header :\n");
  printf ("  %-35s : %x%c%c%c\n", "Magic",ehdr->e_ident[EI_MAG0],ehdr->e_ident[EI_MAG1],
                                 ehdr->e_ident[EI_MAG2],ehdr->e_ident[EI_MAG3]);
  printf ("  %-35s : %s\n", "Class of machine", machine_class(ehdr));
  printf ("  %-35s : %s\n", "Data format", data_format(ehdr));
  printf ("  %-35s : %s\n", "OS / ABI identification", os_abi(ehdr));
  printf ("  %-35s : %s\n", "File type", e_type(ehdr));
  printf ("  %-35s : %s\n", "Machine architecture", e_machine(ehdr));
  printf ("  %-35s : %#x\n", "Entry point", ehdr->e_entry);
  printf ("  %-35s : %-3d (bytes into file)\n", "Start of Program header", ehdr->e_phoff);
  printf ("  %-35s : %-3d (bytes into file)\n", "Start of Section header", ehdr->e_shoff);
  printf ("  %-35s : %#x\n", "Architecture-specific flags", ehdr->e_flags);
  printf ("  %-35s : %d (bytes)\n", "Size of ELF header", ehdr->e_ehsize);
  printf ("  %-35s : %d (bytes)\n", "Size of program header entry", ehdr->e_phentsize);
  printf ("  %-35s : %d\n", "Number of program headers", ehdr->e_phnum);
  printf ("  %-35s : %d (bytes)\n", "Size of section headers", ehdr->e_shentsize);
  printf ("  %-35s : %d\n", "Number of section headers", ehdr->e_shnum);
  printf ("  %-35s : %d\n", "Section header string table index", ehdr->e_shstrndx);
  printf ("\n");
}

void dump_section_headers (void* elf)
{
  int i;
  char buf[6];
  Elf32_Ehdr* ehdr;
  Elf32_Shdr* shdr;
  
  ehdr = elf;
  
  printf ("Section Headers :\n");
  printf ("ther are %d section headers, starting at  %d (bytes into file)\n", ehdr->e_shnum, ehdr->e_shoff);
  printf ("  %-8s","Num");
  printf ("%-20s","Name");
  printf ("%-10s","Type");
  printf ("%-6s","Flg");
  printf ("%-10s","Address");
  printf ("%-8s","Offset");
  printf ("%-6s","Size");
  printf ("%-6s","Link");
  printf ("%-8s","Depends");
  printf ("%-8s","Align B");
  printf ("%-8s","E-Size\n");
  
  shdr = (Elf32_Shdr*)(elf + ehdr->e_shoff);
  for (i=0; i < ehdr->e_shnum; i++) { 
    printf ("  [%2d]%4s",i,"");
    char* sh_name = resolve_section_name (elf, i);
    printf ("%-20s", sh_name);
    printf ("%-10s", sh_type(shdr));
    printf ("%-6s", sh_flags(shdr->sh_flags,buf));
    printf ("%-10.8x", shdr->sh_addr);
    printf ("%-8.6x", shdr->sh_offset);
    printf ("%-6d", shdr->sh_size);
    printf ("%-6d", shdr->sh_link);
    printf ("%-8d", shdr->sh_info);
    printf ("%#-8x", shdr->sh_addralign);
    printf ("%-8d\n", shdr->sh_entsize);
    shdr++;
  }
  
  key_to_flags();
  printf ("\n");
}

void dump_program_headers (void* elf)
{
  int i;
  char buf[6];
  Elf32_Ehdr* ehdr;
  Elf32_Phdr* phdr;
  
  ehdr = elf;
  
  printf ("Program Headers :\n");
  printf ("there are %d program headers, starting at  %d (bytes into file)\n", ehdr->e_phnum, ehdr->e_phoff);
  printf ("  %-8s","Num");
  printf ("%-10s","Type");
  printf ("%-6s","Flg");
  printf ("%-8s","Offset");
  printf ("%-10s","vaddr");
  printf ("%-10s","paddr");
  printf ("%-7s","filesz");
  printf ("%-6s","memsz");
  printf ("%-6s\n","Align");
  
  phdr = (Elf32_Phdr*)(elf + ehdr->e_phoff);
  for (i=0; i < ehdr->e_phnum; i++) { 
    printf ("  [%2d]%4s",i,"");
    printf ("%-10s",  p_type(phdr));
    printf ("%-6s",   p_flags(phdr->p_flags,buf));
    printf ("%-8.6x", phdr->p_offset);
    printf ("%-10.8x", phdr->p_vaddr);
    printf ("%-10.8x", phdr->p_paddr);
    printf ("%-7d", phdr->p_filesz);
    printf ("%-6d", phdr->p_memsz);
    printf ("%#-6x\n", phdr->p_align);
    phdr++;
  }
  printf ("\n");
}

void section_to_segment_map (void* elf)
{
  int i,j;
  Elf32_Ehdr* ehdr;
  Elf32_Phdr* phdr;
  Elf32_Shdr* shdr;
  
  ehdr = elf;
  phdr = (Elf32_Phdr*) (elf + ehdr->e_phoff);
  shdr = (Elf32_Shdr*) (elf + ehdr->e_shoff);
  
  printf ("Section to Segment mapping:\n");
  printf ("  %6s  %s\n","Segment", "Sections");
  for (i=0; i < ehdr->e_phnum; i++) { 
    printf ("   %4d:  ",i);
    for (j=0; j < ehdr->e_shnum; j++) { 
      if ((shdr[j].sh_offset >= phdr[i].p_offset) && 
          (shdr[j].sh_offset < (phdr[i].p_offset + phdr[i].p_filesz))) {
        char* sh_name = resolve_section_name (elf, j);
        printf (" %s,",sh_name);
      }
    }
    printf ("\n");
  }
  printf ("\n");
}

/* type : SHT_SYMTAB, SHT_DYNSYM */
void dump_symbol_table (void* elf, Elf32_Word sh_type)
{
  int i;
  Elf32_Half  sh_symtab_idx;
  Elf32_Shdr* sh_symtab;
  Elf32_Sym*  symtab;
  int         symtab_length;
  
  sh_symtab_idx = get_shdr_id_by_type (elf, 0, sh_type);
  
  sh_symtab     = get_shdr_by_id (elf, sh_symtab_idx);
  symtab        = (Elf32_Sym*) (elf + sh_symtab->sh_offset);
  symtab_length = (sh_symtab->sh_size / sh_symtab->sh_entsize);
    
  printf ("Symbol table '%s' at offset %#x has %d entries.\n", 
                 resolve_section_name (elf, sh_symtab_idx),
                 sh_symtab->sh_offset, symtab_length);
  printf ("%6s:  ","Num");
  printf ("%-9s","Value");
  printf ("%4s ","Size");
  printf ("%-8s","Type");
  printf ("%-7s","Bind");
  printf ("%-17s","Section");
  printf ("%-10s\n","Name");
  
  for (i=0; i < symtab_length; i++) {
    printf ("%6d:  ",i);
    printf ("%-9.8x",symtab->st_value);
    printf ("%4d ",symtab->st_size);
    printf ("%-8s",symbol_type_info(symtab->st_info));
    printf ("%-7s",symbol_bind_info(symtab->st_info));
    if (ELF32_ST_TYPE(symtab->st_info) != STT_FILE)
      printf ("%-17s", resolve_section_name (elf, symtab->st_shndx));
    else
      printf ("%-17s","");
    printf ("%-10s\n",resolve_symbol_name (elf, sh_symtab, symtab->st_name));
    symtab++;
  }
  printf ("\n");
  
}

/*dump relocation sections*/
void dump_rel_section (void* elf)
{
  int i;
  Elf32_Ehdr* ehdr;
  Elf32_Shdr* sh_symtab;
  Elf32_Sym* symtab;
  Elf32_Shdr* sh_rel;
  int         sh_rel_idx;
  Elf32_Rel* reltab;
  
  ehdr = elf;
  
  if (ehdr->e_type == ET_REL)
    sh_symtab = get_shdr_by_type (elf, SHT_SYMTAB);
  else if (ehdr->e_type == ET_EXEC || ehdr->e_type == ET_DYN || ehdr->e_type == ET_CORE)
    sh_symtab = get_shdr_by_type (elf, SHT_DYNSYM);
  else {
    perror ("Header has un unknown type!");
    return;
  }  
    
  symtab = (Elf32_Sym*) (elf + sh_symtab->sh_offset);
  
  sh_rel_idx = get_shdr_id_by_type (elf, 0, SHT_REL);
  if (sh_rel_idx < 0) {
    printf ("\nNo Relocations  in this file!\n");
    return;
  }
  
  do {
    sh_rel = get_shdr_by_id (elf, sh_rel_idx);
    reltab = (Elf32_Rel*) (elf + sh_rel->sh_offset);
  
    printf ("Relocation section '%s' at offset %#x:\n", resolve_section_name (elf, sh_rel_idx), sh_rel->sh_offset);
    printf ("%6s:  ","Num");
    printf ("%-9s","Offset");
    printf ("%-9s","Info");
    printf ("%-25s","Type");
    printf ("%-12s","Sym. value");
    printf ("%-12s\n","Sym. name");
    int reltab_length = (sh_rel->sh_size / sh_rel->sh_entsize);
    for (i=0; i < reltab_length; i++) {
      printf ("%6d:  ",i);
      printf ("%-9.8x",reltab->r_offset);
      printf ("%-9.8x",reltab->r_info);
      Elf32_Word sym_id = ELF32_R_SYM (reltab->r_info);
      Elf32_Word r_type = ELF32_R_TYPE (reltab->r_info);
      printf ("%-25s", rel_type(r_type));
      printf ("%-12.8x", symtab[sym_id].st_value);
      printf ("%-12s\n", resolve_symbol_name (elf, sh_symtab, symtab[sym_id].st_name));
      reltab++;
    }
    printf ("\n");
    sh_rel_idx = get_shdr_id_by_type (elf, sh_rel_idx+1, SHT_REL); 
  } while (sh_rel_idx >= 0);
}

void read_elf_binary (const char* filename, char* opt)
{
  void* elf;
  
  elf = load_elf_binary (filename);
  
  if (!strcmp (opt, "-h") || !strcmp (opt, "-a"))
    dump_elf_header (elf);
  if (!strcmp (opt, "-l") || !strcmp (opt, "-a")) {
    dump_program_headers (elf);
    section_to_segment_map (elf);
  }
  if (!strcmp (opt, "-S") || !strcmp (opt, "-a"))
   dump_section_headers (elf);
  if (!strcmp (opt, "-s") || !strcmp (opt, "-a")) {
    dump_symbol_table (elf, SHT_DYNSYM);
    dump_symbol_table (elf, SHT_SYMTAB);
  }
  if (!strcmp (opt, "-r") || !strcmp (opt, "-a"))
    dump_rel_section (elf);

}


int
main (int nargs, char** argv)
{
  char* opt = "";
  char* filename = "/usr/local/test/a1.o";
  
  
  if (nargs == 2)
    filename = argv[1];
  else if (nargs == 3) {
    opt = argv[1];
    filename = argv[2];
  }
  
  read_elf_binary (filename, opt);
  
}