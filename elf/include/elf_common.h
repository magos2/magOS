/*-
 * Copyright (c) 1998 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/sys/elf_common.h,v 1.11 2002/08/11 21:07:50 robert Exp $
 */

#ifndef _SYS_ELF_COMMON_H_
#define _SYS_ELF_COMMON_H_ 1

#include <stdint.h>

/*
 * ELF definitions that are independent of architecture or word size.
 */

/*
 * Note header.  The ".note" section contains an array of notes.  Each
 * begins with this header, aligned to a word boundary.  Immediately
 * following the note header is n_namesz bytes of name, padded to the
 * next word boundary.  Then comes n_descsz bytes of descriptor, again
 * padded to a word boundary.  The values of n_namesz and n_descsz do
 * not include the padding.
 */

typedef struct {
	uint32_t	n_namesz;	/* Length of name. */
	uint32_t	n_descsz;	/* Length of descriptor. */
	uint32_t	n_type;		/* Type of this note. */
} Elf_Note;

/* Indexes into the e_ident array.  Keep synced with 
   http://www.sco.com/developer/gabi/ch4.eheader.html */
#define EI_MAG0		0	/* Magic number, byte 0. */
#define EI_MAG1		1	/* Magic number, byte 1. */
#define EI_MAG2		2	/* Magic number, byte 2. */
#define EI_MAG3		3	/* Magic number, byte 3. */
#define EI_CLASS	   4	/* Class of machine. */
#define EI_DATA		5	/* Data format. */
#define EI_VERSION	 6	/* ELF format version. */
#define EI_OSABI	   7	/* Operating system / ABI identification */
#define EI_ABIVERSION  8	/* ABI version */
#define OLD_EI_BRAND   8	/* Start of architecture identification. */
#define EI_PAD		 9	/* Start of padding (per SVR4 ABI). */
#define EI_NIDENT	 16	/* Size of e_ident array. */

/* Values for the magic number bytes. */
#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'
#define ELFMAG		"\177ELF"	/* magic string */
#define SELFMAG		4		/* magic string size */

/* Values for e_ident[EI_VERSION] and e_version. */
#define EV_NONE	   0
#define EV_CURRENT	1

/* Values for e_ident[EI_CLASS]. */
#define ELFCLASSNONE  0	/* Unknown class. */
#define ELFCLASS32	1	/* 32-bit architecture. */
#define ELFCLASS64	2	/* 64-bit architecture. */


/* Values for e_ident[EI_DATA]. */
#define ELFDATANONE	0	/* Unknown data format. */
#define ELFDATA2LSB	1	/* 2's complement little-endian. */
#define ELFDATA2MSB	2	/* 2's complement big-endian. */

/* Values for e_ident[EI_OSABI]. */
#define ELFOSABI_SYSV		0	/* UNIX System V ABI */
#define ELFOSABI_NONE		ELFOSABI_SYSV	/* symbol used in old spec */
#define ELFOSABI_HPUX		1	/* HP-UX operating system */
#define ELFOSABI_NETBSD	  2	/* NetBSD */
#define ELFOSABI_LINUX	   3	/* GNU/Linux */
#define ELFOSABI_HURD		4	/* GNU/Hurd */
#define ELFOSABI_86OPEN	  5	/* 86Open common IA32 ABI */
#define ELFOSABI_SOLARIS	 6	/* Solaris */
#define ELFOSABI_MONTEREY	7	/* Monterey */
#define ELFOSABI_IRIX		8	/* IRIX */
#define ELFOSABI_FREEBSD	 9	/* FreeBSD */
#define ELFOSABI_TRU64	  10	/* TRU64 UNIX */
#define ELFOSABI_MODESTO	11	/* Novell Modesto */
#define ELFOSABI_OPENBSD	12	/* OpenBSD */
#define ELFOSABI_ARM		97	/* ARM */
#define ELFOSABI_STANDALONE 255   /* Standalone (embedded) application */

/* e_ident */
#define IS_ELF(ehdr)	((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
			 (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
			 (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
			 (ehdr).e_ident[EI_MAG3] == ELFMAG3)

/* Values for e_type. */
#define ET_NONE		0	/* Unknown type. */
#define ET_REL		 1	/* Relocatable. */
#define ET_EXEC		2	/* Executable. */
#define ET_DYN		 3	/* Shared object. */
#define ET_CORE		4	/* Core file. */

/* Values for e_machine. */
#define EM_NONE	   0	/* Unknown machine. */
#define EM_M32		1	/* AT&T WE32100. */
#define EM_SPARC  	2	/* Sun SPARC. */
#define EM_386		3	/* Intel i386. */
#define EM_68K		4	/* Motorola 68000. */
#define EM_88K		5	/* Motorola 88000. */
#define EM_486		6	/* Intel i486. */
#define EM_860		7	/* Intel i860. */
#define EM_MIPS   	8	/* MIPS R3000 Big-Endian only */

/* Extensions.  This list is not complete. */
#define EM_S370		    9	/* IBM System/370 */
#define EM_MIPS_RS4_BE	10	/* MIPS R4000 Big-Endian */ /* Depreciated */
#define EM_PARISC	     15	/* HPPA */
#define EM_SPARC32PLUS	18	/* SPARC v8plus */
#define EM_PPC		    20	/* PowerPC 32-bit */
#define EM_PPC64	      21	/* PowerPC 64-bit */
#define EM_ARM		    40	/* ARM */
#define EM_SPARCV9	    43	/* SPARC v9 64-bit */
#define EM_IA_64	      50	/* Intel IA-46 Processor */
#define EM_X86_64	     62	/* Advanced Micro Devices x86-64 */
#define EM_ALPHA	  0x9026	/* Alpha (written in the absence of an ABI */

/* Special section indexes. */
#define SHN_UNDEF	         0		/* Undefined, missing, irrelevant. */
#define SHN_LORESERVE	0xff00		/* First of reserved range. */
#define SHN_LOPROC	   0xff00		/* First processor-specific. */
#define SHN_HIPROC	   0xff1f		/* Last processor-specific. */
#define SHN_ABS		  0xfff1		/* Absolute values. */
#define SHN_COMMON	   0xfff2		/* Common data. */
#define SHN_HIRESERVE	0xffff		/* Last of reserved range. */

/* sh_type */
#define SHT_NULL	    0		/* inactive */
#define SHT_PROGBITS	1		/* program defined information */
#define SHT_SYMTAB	  2		/* symbol table section */
#define SHT_STRTAB	  3		/* string table section */
#define SHT_RELA	    4		/* relocation section with addends */
#define SHT_HASH	    5		/* symbol hash table section */
#define SHT_DYNAMIC	 6		/* dynamic section */ 
#define SHT_NOTE	    7		/* note section */
#define SHT_NOBITS	  8		/* no space section */
#define SHT_REL		 9		/* relocation section - no addends */
#define SHT_SHLIB	  10		/* reserved - purpose unknown */
#define SHT_DYNSYM	 11		/* dynamic symbol table section */ 
#define SHT_NUM		12		/* number of section types */
#define SHT_LOPROC	0x70000000	/* reserved range for processor */
#define SHT_HIPROC	0x7fffffff	/* specific section header types */
#define SHT_LOUSER	0x80000000	/* reserved range for application */
#define SHT_HIUSER	0xffffffff	/* specific indexes */

/* Flags for sh_flags. */
#define SHF_WRITE	    0x1		/* Section contains writable data. */
#define SHF_ALLOC	    0x2		/* Section occupies memory. */
#define SHF_EXECINSTR	0x4		/* Section contains instructions. */
#define SHF_MASKPROC	0xf0000000  /* Reserved for processor-specific. */

/* Values for p_type. */
#define	PT_NULL		0		/* Program header table entry unused */
#define    PT_LOAD		1		/* Loadable program segment */
#define    PT_DYNAMIC 	2		/* Dynamic linking information */
#define    PT_INTERP	  3		/* Program interpreter */
#define    PT_NOTE		4		/* Auxiliary information */
#define    PT_SHLIB	   5		/* Reserved */
#define    PT_PHDR		6		/* Entry for header table itself */
#define    PT_TLS		 7		/* Thread-local storage segment */
#define	PT_NUM	 	8		/* Number of defined types */
#define    PT_LOOS		0x60000000	/* Start of OS-specific */
#define    PT_GNU_EH_FRAME	0x6474e550	/* GCC .eh_frame_hdr segment */
#define    PT_GNU_STACK	0x6474e551	/* Indicates stack executability */
#define    PT_GNU_RELRO	0x6474e552	/* Read-only after relocation */
#define    PT_SUNWBSS  	0x6ffffffa	/* Sun Specific segment */
#define    PT_SUNWSTACK	0x6ffffffb	/* Stack segment */
#define    PT_HIOS		 0x6fffffff	/* End of OS-specific */
#define    PT_LOPROC	   0x70000000	/* Start of processor-specific */
#define    PT_HIPROC	   0x7fffffff	/* End of processor-specific */

/* Processor specific values for the Phdr p_type field.  */
#define PT_ARM_EXIDX		(PT_LOPROC + 1)	/* ARM unwind segment.  */

#define PT_COUNT	7	/* Number of defined p_type values. */


/* Values for p_flags. */
#define PF_X		0x1	/* Executable. */
#define PF_W		0x2	/* Writable. */
#define PF_R		0x4	/* Readable. */

/* Values for d_tag. */
#define DT_NULL      0	/* Terminating entry. */
#define DT_NEEDED	1	/* String table offset of a needed shared library. */
#define DT_PLTRELSZ  2	/* Total size in bytes of PLT relocations. */
#define DT_PLTGOT    3	/* Processor-dependent address. */
#define DT_HASH	  4	/* Address of symbol hash table. */
#define DT_STRTAB	5	/* Address of string table. */
#define DT_SYMTAB	6	/* Address of symbol table. */
#define DT_RELA	  7	/* Address of ElfNN_Rela relocations. */
#define DT_RELASZ	8	/* Total size of ElfNN_Rela relocations. */
#define DT_RELAENT   9	/* Size of each ElfNN_Rela relocation entry. */
#define DT_STRSZ	10	/* Size of string table. */
#define DT_SYMENT   11	/* Size of each symbol table entry. */
#define DT_INIT	 12	/* Address of initialization function. */
#define DT_FINI	 13	/* Address of finalization function. */
#define DT_SONAME   14	/* String table offset of shared object name. */
#define DT_RPATH	15	/* String table offset of library path. */
#define DT_SYMBOLIC 16	/* Indicates "symbolic" linking. */
#define DT_REL	  17	/* Address of ElfNN_Rel relocations. */
#define DT_RELSZ	18	/* Total size of ElfNN_Rel relocations. */
#define DT_RELENT   19	/* Size of each ElfNN_Rel relocation. */
#define DT_PLTREL   20	/* Type of relocation used for PLT. */
#define DT_DEBUG	21	/* Reserved (not used). */
#define DT_TEXTREL  22	/* Indicates there may be relocations in
				             non-writable segments. */
#define DT_JMPREL   23	/* Address of PLT relocations. */

#define DT_COUNT	24	/* Number of defined d_tag values. */

/* Values for n_type.  Used in core files. */
#define NT_PRSTATUS	1	/* Process status. */
#define NT_FPREGSET	2	/* Floating point registers. */
#define NT_PRPSINFO	3	/* Process state info. */

/* Symbol Binding - ELFNN_ST_BIND - st_info */
#define STB_LOCAL	  0	/* Local symbol */
#define STB_GLOBAL	 1	/* Global symbol */
#define STB_WEAK	   2	/* like global - lower precedence */
#define STB_LOPROC	13	/* reserved range for processor */
#define STB_HIPROC	15	/*  specific symbol bindings */

/* Symbol type - ELFNN_ST_TYPE - st_info */
#define STT_NOTYPE	 0	/* Unspecified type. */
#define STT_OBJECT	 1	/* Data object. */
#define STT_FUNC	   2	/* Function. */
#define STT_SECTION    3	/* Section. */
#define STT_FILE	   4	/* Source file. */
#define STT_LOPROC	13	/* reserved range for processor */
#define STT_HIPROC	15	/*  specific symbol types */

/* Special symbol table indexes. */
#define STN_UNDEF	0	/* Undefined symbol index. */

/* ARM relocs. uncomplete  */
#define R_ARM_NONE	 	0	/* No reloc */
#define R_ARM_ABS32		2	/* Direct 32 bit  */
#define R_ARM_REL32		3	/* PC relative 32 bit */
#define R_ARM_PC13		 4
#define R_ARM_ABS16		5	/* Direct 16 bit */
#define R_ARM_ABS12		6	/* Direct 12 bit */
#define R_ARM_THM_ABS5	 7	/* Direct & 0x7C (LDR, STR).  */
#define R_ARM_ABS8	 	8	/* Direct 8 bit */
#define R_ARM_SBREL32  	9
#define R_ARM_THM_CALL	10	/* PC relative 24 bit (Thumb32 BL).  */
#define R_ARM_THM_PC8	 11	/* PC relative & 0x3FC (Thumb16 LDR, ADD, ADR).  */
#define R_ARM_TLS_DESC	13    /* Dynamic relocation.  */
#define R_ARM_COPY		20	/* Copy symbol at runtime */
#define R_ARM_GLOB_DAT	21	/* Create GOT entry */
#define R_ARM_JUMP_SLOT   22	/* Create PLT entry */
#define R_ARM_RELATIVE	23	/* Adjust by program base */
#define R_ARM_GOTOFF	  24	/* 32 bit offset to GOT */
#define R_ARM_GOTPC	   25	/* 32 bit PC relative offset to GOT */
#define R_ARM_GOT32	   26	/* 32 bit GOT entry */
#define R_ARM_PLT32	   27	/* Deprecated, 32 bit PLT address.  */
#define R_ARM_CALL		28	/* PC relative 24 bit (BL, BLX).  */
#define R_ARM_JUMP24	  29	/* PC relative 24 bit (B, BL<cond>).  */
#define R_ARM_THM_JUMP24  30	/* PC relative 24 bit (Thumb32 B.W).  */
#define R_ARM_BASE_ABS	31	/* Adjust by program base.  */
#define R_ARM_SBREL31	 39	/* Program base relative.  */
#define R_ARM_MOVW_ABS_NC 43	/* Direct 16-bit (MOVW).  */
#define R_ARM_MOVT_ABS	44	/* Direct high 16-bit (MOVT).  */
#define R_ARM_MOVW_PREL_NC     45	/* PC relative 16-bit (MOVW).  */
#define R_ARM_MOVT_PREL		46	/* PC relative (MOVT).  */
#define R_ARM_THM_MOVW_ABS_NC  47	/* Direct 16 bit (Thumb32 MOVW).  */
#define R_ARM_THM_MOVT_ABS	 48	/* Direct high 16 bit  (Thumb32 MOVT).  */
#define R_ARM_GOT_ABS		  95	/* GOT entry.  */
#define R_ARM_GOT_PREL	 	96	/* PC relative GOT entry.  */

#endif /* !_SYS_ELF_COMMON_H_ */