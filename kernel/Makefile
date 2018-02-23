EXE     = kernel.bin
OUT_DIR = ../bin/kernel
SRC     = $(wildcard *.c) 
KERN_O  = $(SRC:.c=.o) sys_call.o
KERN    = $(addprefix $(OUT_DIR)/, $(KERN_O)) 
MM      = $(wildcard ../bin/mm/*.o)
FS      = $(wildcard ../bin/fs/*.o ../bin/fs/ext2/*.o )
DRIVERS = $(wildcard ../bin/drivers/char/*.o) $(wildcard ../bin/drivers/block/*.o)
MBOOT   = $(OUT_DIR)/../boot/multiboot.o

objs    = $(MBOOT) $(OUT_DIR)/../boot/head.o $(KERN) $(MM) $(FS) $(DRIVERS) 

all:$(OUT_DIR)/$(EXE)

$(OUT_DIR)/%.o:%.S
	$(CC) $(CFLAGS) -c $< -o $@
$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

# Linux trick	
# Generate section listing all symbols and add it into vmlinux
#	It's a three stage process:
#	o .tmp_vmlinux1 has all symbols and sections, but __kallsyms is
#	  empty
#	  Running kallsyms on that gives us .tmp_kallsyms1.o with
#	  the right size
#	o .tmp_vmlinux2 now has a __kallsyms section of the right size,
#	  but due to the added section, some addresses have shifted
#	  From here, we generate a correct .tmp_kallsyms2.o
#	o The correct .tmp_kallsyms2.o is linked into the final vmlinux.
cmd_ld      = $(LD) -n -T linker.ld $(objs) $(OUT_DIR)/$(1) -o $@
cmd_objcopy = $(OBJCOPY)  --only-keep-debug $@ $(OUT_DIR)/kernel-debug.sym
cmd_strip   = $(OBJCOPY)  --strip-debug $@
cmd_ksyms   = $(NM) -n $@ | $(KALLSYMS) > $(1)
cmd_s_to_o  = $(CC) $(CFLAGS) -c $(1).S -o $(OUT_DIR)/$(1).o

$(OUT_DIR)/.tmp_kernel1.elf: $(objs) $(OUT_DIR)/kallsyms_ld.o
	@echo Kernel linking: stage 1
	$(call cmd_ld,kallsyms_ld.o)
	$(call cmd_ksyms,.tmp_kallsyms1.S)
	$(call cmd_s_to_o,.tmp_kallsyms1)
	
$(OUT_DIR)/.tmp_kernel2.elf: $(OUT_DIR)/.tmp_kernel1.elf $(OUT_DIR)/.tmp_kallsyms1.o
	@echo Kernel linking: stage 2
	$(call cmd_ld,.tmp_kallsyms1.o)
	$(call cmd_ksyms,.tmp_kallsyms2.S)
	$(call cmd_s_to_o,.tmp_kallsyms2)
	
$(OUT_DIR)/kernel.elf: $(OUT_DIR)/.tmp_kernel2.elf $(OUT_DIR)/.tmp_kallsyms2.o
	@echo Kernel linking: stage 3
	$(call cmd_ld,.tmp_kallsyms2.o)
	$(cmd_objcopy)
	$(cmd_strip)
	
$(OUT_DIR)/kernel.bin:$(OUT_DIR)/kernel.elf
	$(OBJCOPY) -O binary $<  $@
	
clean:
	rm -f $(OUT_DIR)/$(EXE) $(objs) $(OUT_DIR)/kernel.elf $(OUT_DIR)/.tmp_kernel*.elf

