EXE = shell
SRC = crt/crt0.c  $(wildcard *.c libc/*.c) 
OBJ = $(SRC:.c=.o)

LD_ENTRY = 0x400000

OUT_DIR = ../bin/usr
objs := $(addprefix $(OUT_DIR)/, $(OBJ))

UINCLUDE = -I./libc/include -I../include -I../include/asm/$(TARGET)
UCFLAGS = -Wall -g -fno-builtin -nostdinc   $(UINCLUDE) $(GCC_INCLUDE)

all: $(OUT_DIR)/$(EXE)

cmd_objcopy = $(OBJCOPY)  --only-keep-debug $@ $(OUT_DIR)/user-debug.sym
cmd_strip = $(OBJCOPY)  --strip-debug $@

$(OUT_DIR)/%.o:%.c
	$(CC) $(UCFLAGS) -c  $< -o $@
	
$(OUT_DIR)/shell.elf: $(objs)
	$(LD) -Ttext $(LD_ENTRY) $^ -o $@
	$(cmd_objcopy)
	$(cmd_strip)
	
$(OUT_DIR)/shell:$(OUT_DIR)/shell.elf
	$(OBJCOPY) -O binary $<  $@

int:
	mkdir -p $(OUT_DIR)/libc
	mkdir -p $(OUT_DIR)/crt
	
clean:
	rm -f $(objs)

