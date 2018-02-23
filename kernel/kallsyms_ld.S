#if BITS_PER_LONG == 64
#define PTR .quad
#define ALGN .align 8
#else
#define PTR .long
#define ALGN .align 4
#endif
.data
.globl kallsyms_addresses
	ALGN
kallsyms_addresses:

.globl kallsyms_num_syms
	ALGN
kallsyms_num_syms:
	PTR	168

.globl kallsyms_names
	ALGN
kallsyms_names:





