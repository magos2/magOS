EXE=list_test.bin  bitops_test.bin memory_test.bin kmalloc_test.bin mm_test.bin
SRC= $(wildcard *.c) 
OBJ= $(SRC:.c=.o) 

OUT_DIR=../bin/test
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 
INSTALL_DIR=/usr/local/test

all:$(addprefix $(OUT_DIR)/, $(EXE)) install

KERNEL_OPTIONS=-DKERNEL_UNIT_TEST

#TARGET=armhf
TARGET=terminalide

ifeq ($(TARGET), x86)
GCC_ARCH=i386-elf
GCC_VERSION=4.9.2
GCC_INCLUDE=-I/opt/cross/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
endif
ifeq ($(TARGET), armhf)
GCC_ARCH=arm-linux-gnueabihf
GCC_VERSION=4.9.2
GCC_INCLUDE=-I/usr/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
endif
ifeq ($(TARGET), terminalide)
GCC_ARCH=terminal
GCC_VERSION=4.4.0
GCC_INCLUDE=-I~/android-gcc-$(GCC_VERSION)/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include
INSTALL_DIR=~/local/bin
INCLUDE= -I../include/asm/armhf
endif

INCLUDE+= -I../include -I../include/asm/$(TARGET) -I/usr/include/
#GCC_INCLUDE=-I/usr/lib/gcc/i686-redhat-linux/4.4.7/include
#GCC_INCLUDE=-I/usr/lib/gcc/arm-linux-gnueabihf/4.9/include -I/usr/include/arm-linux-gnueabihf
AS=$(GCC_ARCH)-as
LD=$(GCC_ARCH)-ld 
CC=$(GCC_ARCH)-gcc
CFLAGS+= -Wall -g $(KERNEL_OPTIONS)  $(INCLUDE) $(GCC_INCLUDE)


$(OUT_DIR)/memory_test.o:memory_test.c
	$(CC) $(CFLAGS) -fno-builtin-fork -fno-builtin-execv  -c  $< -o $@
	
$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

$(OUT_DIR)/list_test.bin:$(OUT_DIR)/list_test.o   
	$(CC) $^ -o $@

# cannot be tested on arm because harcodeid x86
#$(OUT_DIR)/string_test:$(OUT_DIR)/string_test.o
	#$(CC) $^ -o $@


$(OUT_DIR)/bitops_test.bin:$(OUT_DIR)/bitops_test.o   
	$(CC) $^ -o $@

$(OUT_DIR)/sched_test.bin:$(OUT_DIR)/ext2_test.o $(OUT_DIR)/../fs/ext2.o
	$(CC) $^ -o $@

$(OUT_DIR)/memory_test.bin:$(OUT_DIR)/memory_test.o $(OUT_DIR)/mocks_magos.o $(OUT_DIR)/../mm/memory.o
	$(CC) -fno-builtin-fork -fno-builtin-execv $^ -o $@
	
$(OUT_DIR)/kmalloc_test.bin:$(OUT_DIR)/kmalloc_test.o  $(OUT_DIR)/mocks_magos.o $(OUT_DIR)/../mm/memory.o $(OUT_DIR)/../mm/kmalloc.o $(OUT_DIR)/../mm/vmalloc.o
	$(CC)  $^ -o $@

$(OUT_DIR)/mm_test.bin:$(OUT_DIR)/mm_test.o  $(OUT_DIR)/mocks_magos.o $(OUT_DIR)/../mm/mm.o
	$(CC)  $^ -o $@
	
install:
	cp $(OUT_DIR)/*.bin $(INSTALL_DIR)
	chmod +x $(INSTALL_DIR)/*.bin
	
clean:
	rm -f $(addprefix $(OUT_DIR)/, $(EXE)) $(OUT_OBJ)
