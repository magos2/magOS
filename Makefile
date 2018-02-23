# Master Makefile. by Abderrahim Rahali. Copyright 2016.
#
# to compile kernel for a target, specify TARGET variable. 
# you can also do it by make: "make -e TARGET=x86" 
# to compile kernel for unit tests under userspace, you must add "-DKERNEL_UNIT_TEST" in kernel_options variable.
# image layout : 
#        0-512B      boot sector
#        512B-1MiB   kernel binary
#        1MiB-2MiB   ext2 partition,contains user binary
#     dd if=/dev/zero of=hd-magos.img bs=512 count=4000  : create 2MB image
#     dd if=/dev/zero of=hd-magos.img.0 bs=512 count=2000 : create 1MB image
#     fdisk hd-magos.img  ; create 2 partions, each of 1MiB
#         then saisir : n p 1 2000 a 
#                       n p 2001 3999 w
#     mkfs.ext2  hd-magos.img.0   
#OBJ=floppyA.img
OBJ           = magos.img
OUT_DIR       = ./bin
INSTALL_DIR   = /usr/local/images
KERN_ISO      = $(INSTALL_DIR)/magos.iso
KERN_IMG      = $(INSTALL_DIR)/disk.img     
KERN_IMG_SIZE = 100  #in kiB

TARGET = x86
#TARGET= armhf
#TARGET= terminalide
export TARGET

#KERNEL_OPTIONS = -DKERNEL_UNIT_TEST
CFLAGS += -g
CFLAGS += -O0
#CFLAGS += -Werror

ifeq ($(TARGET), x86)
GCC_ARCH    = i386-elf
GCC_VERSION = 4.9.2
GCC_INCLUDE = -I/opt/cross/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
endif
ifeq ($(TARGET), armhf)
GCC_ARCH    = arm-linux-gnueabihf
GCC_VERSION = 4.9.2
GCC_INCLUDE = -I/usr/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
endif
ifeq ($(TARGET), terminalide)
GCC_ARCH    = terminal
GCC_VERSION = 4.4.0
GCC_INCLUDE = -I~/android-gcc-$(GCC_VERSION)/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
INSTALL_DIR = ~/local/bin
INCLUDE     = -I../include/asm/armhf
endif

INCLUDE += -I../include -I../include/asm/$(TARGET) 
AS       = $(GCC_ARCH)-as
LD       = $(GCC_ARCH)-ld
CC       = $(GCC_ARCH)-gcc
OBJCOPY  = $(GCC_ARCH)-objcopy
NM       = nm
KALLSYMS = kallsyms
MAKE     = make --no-print-directory
GENEXT2FS= /opt/genext2fs/bin/genext2fs
CFLAGS  += -Wall $(KERNEL_OPTIONS) -fno-builtin -nostdinc -fno-omit-frame-pointer   $(INCLUDE) $(GCC_INCLUDE)

export AS
export LD
export CC
export OBJCOPY
export CFLAGS
export NM
export KALLSYMS

all:$(OBJ) 

# The .PHONY rule means that project_code is not a file that needs to be built
.PHONY: drivers mm fs usr kernel boot scripts magos.img

floppyA.img:drivers mm fs test usr kernel boot
	@echo --------FLOPPY----------
	cat $(OUT_DIR)/boot/bootsect.bin $(OUT_DIR)/boot/setup.bin $(OUT_DIR)/kernel/kernel.bin /dev/zero | dd of=$@ bs=512 count=2880
	mv -f $@ $(KERNEL_INSTALL_PATH)/

magos.img.old:boot kernel usr test
	@echo --------HD Image---------
	cat $(OUT_DIR)/boot/bootsect.bin |dd status=none of=$(KERN_IMG) conv=nocreat,notrunc bs=446 count=1
	cat $(OUT_DIR)/boot/setup.bin $(OUT_DIR)/kernel/kernel.bin /dev/zero |dd status=none of=$(KERN_IMG) iflag=fullblock conv=nocreat,notrunc seek=1 bs=512 count=200 
	debugfs -w -f ./debugfs.cmd $(KERN_IMG).0
	cat $(KERN_IMG).0 |dd status=none of=$(KERN_IMG) conv=nocreat,notrunc seek=2000 bs=512 count=2000

magos.img:kernel boot usr test
	@echo ---------ISO-------------
	cp $(OUT_DIR)/kernel/kernel.elf $(INSTALL_DIR)/out/boot/
	cp $(OUT_DIR)/usr/shell $(INSTALL_DIR)/out/usr/bin/
	#use -x option to evoid deleting partition table
	$(GENEXT2FS) -b $(KERN_IMG_SIZE) -d $(INSTALL_DIR)/out/ -x $(KERN_IMG) $(KERN_IMG)
	
iso:init
	mkdir -p $(INSTALL_DIR)/iso/boot/grub
	cp ./grub.cfg $(INSTALL_DIR)/iso/boot/grub/
	grub-mkrescue --compress=no --modules="ext2 elf vga echo multiboot" -o $(KERN_ISO) $(INSTALL_DIR)/iso
	mkdir -p $(INSTALL_DIR)/boot/
	$(GENEXT2FS) -b $(KERN_IMG_SIZE) -d $(INSTALL_DIR)/out/  $(KERN_IMG)
	(echo d; echo w) | fdisk $(KERN_IMG) 
	(echo n; echo p; echo 1; echo 1;echo -e '\n';echo w) | fdisk $(KERN_IMG)
	
boot:
	@echo ---------BOOT------------
	$(MAKE) -C boot
	
head:
	@echo ---------HEAD------------
	$(MAKE) -C boot head
	
drivers:
	@echo --------DRIVERS----------
	$(MAKE)  -C drivers

mm:
	@echo ---------MM--------------
	$(MAKE)  -C mm

fs:
	@echo ---------FS--------------
	$(MAKE)  -C fs

test:
	@echo ---------Test------------
	$(MAKE)  -C test

usr:
	@echo ---------USR-------------
	$(MAKE)  -C usr
	
kernel: head drivers mm fs 
	@echo ---------KERNEL----------
	$(MAKE)  -C kernel

scripts:
	@echo ---------SCRIPTS----------
	$(MAKE)  -C scripts
	
init:
	mkdir -p $(OUT_DIR)/boot 
	mkdir -p $(OUT_DIR)/kernel 
	mkdir -p $(OUT_DIR)/mm 
	mkdir -p $(OUT_DIR)/fs/ext2
	mkdir -p $(OUT_DIR)/drivers/char
	mkdir -p $(OUT_DIR)/drivers/block
	mkdir -p $(OUT_DIR)/test
	mkdir -p $(OUT_DIR)/scripts
	mkdir -p $(OUT_DIR)/usr/libc
	mkdir -p $(OUT_DIR)/usr/crt
	mkdir -p $(INSTALL_DIR)/out/boot
	mkdir -p $(INSTALL_DIR)/out/usr/bin
	
clean:
	$(MAKE) -C boot clean
	$(MAKE) -C kernel clean
	$(MAKE) -C mm clean
	$(MAKE) -C fs clean
	$(MAKE) -C drivers clean
	$(MAKE) -C usr clean
	
dist-clean: clean
	rm -rf $(INSTALL_DIR)/out $(INSTALL_DIR)/iso $(KERN_IMG) $(KERN_ISO)
	
	
	
