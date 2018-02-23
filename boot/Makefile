EXE     = bootsect.bin setup.bin
SRC_DIR = ./$(TARGET)
SRC     = $(wildcard *.S)
OBJ     = $(SRC:.S=.o)

OUT_DIR = ../bin/boot
OUT_EXE = $(addprefix $(OUT_DIR)/, $(EXE)) 
OUT_OBJ = $(addprefix $(OUT_DIR)/, bootsect.o setup.o multiboot.o head.o )
OUT_HEAD= $(addprefix $(OUT_DIR)/, multiboot.o head.o)
#if not using grub
#syssize = `ls -s ../bin/kernel/kernel.bin|cut -d' ' -f1`
syssize = 200
CFLAGS += -O0

all:$(OUT_EXE)

head:$(OUT_HEAD) 

$(OUT_DIR)/bootsect.o:$(SRC_DIR)/bootsect.S
	@echo sysize=$(syssize)
	$(CC) $(CFLAGS) -Dsyssize=$(syssize) -c $< -o $@
	
$(OUT_DIR)/setup.o:$(SRC_DIR)/setup.S
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OUT_DIR)/head.o:$(SRC_DIR)/head.S
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OUT_DIR)/multiboot.o:$(SRC_DIR)/multiboot.S
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OUT_DIR)/bootsect.bin:$(OUT_DIR)/bootsect.o
	$(LD) --oformat binary -Ttext 0x0  $^ -o $@

$(OUT_DIR)/setup.bin:$(OUT_DIR)/setup.o
	$(LD) --oformat binary -Ttext 0x0  $^ -o $@

clean:
	rm -f $(OUT_EXE) $(OUT_OBJ) 
