EXE=kallsyms
SRC= $(wildcard *.c) 
OBJ= $(SRC:.c=.o) 

OUT_DIR=../bin/scripts
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 
INSTALL_DIR=/usr/local/bin

all:$(addprefix $(OUT_DIR)/, $(EXE)) install

TARGET=armhf
TARGET=x86

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

GCC_ARCH=x86_64-linux-gnu
GCC_VERSION=5
GCC_INCLUDE=-I/opt/cross/lib/gcc/$(GCC_ARCH)/$(GCC_VERSION)/include

INCLUDE+=  -I/usr/include/
AS=as
LD=ld 
CC=gcc
CFLAGS+= -Wall -g $(INCLUDE) $(GCC_INCLUDE)
	
$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

$(OUT_DIR)/kallsyms:$(OUT_DIR)/kallsyms.o   
	$(CC) $^ -o $@

install:
	cp $(addprefix $(OUT_DIR)/, $(EXE)) $(INSTALL_DIR)
	chmod +x $(addprefix $(INSTALL_DIR)/, $(EXE))
	
clean:
	rm -f $(addprefix $(OUT_DIR)/, $(EXE)) $(OUT_OBJ)
