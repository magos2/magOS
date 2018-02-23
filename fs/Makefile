SRC= $(wildcard *.c ext2/*.c) 
OBJ= $(SRC:.c=.o) 

OUT_DIR=../bin/fs
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ))

all:$(OUT_OBJ)

$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OUT_OBJ)
