#ifndef _CONFIG_H
#define _CONFIG_H

#define BOOTSEG  0x07c0  /* Bootsect will be loaded here by the BIOS */
#define INITSEG  0x9000  /* Bootsect move itself at 0x90000 */
#define SETUPSEG 0x9020  /* setup.S loaded at 0x90200(0x90000+512B) */
#define SYSSEG   0x100   /* kernel loaded at 0x1000(4kB) */

#define SETUPLEN 4       /* nb of setup sector's*/

#endif
