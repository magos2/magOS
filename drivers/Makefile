SRC_CHAR= $(wildcard ./char/*.c)
SRC_BLOCK= $(wildcard ./block/*.c)
OBJ= $(SRC_CHAR:.c=.o) $(SRC_BLOCK:.c=.o)

OUT_DIR=../bin/drivers
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 

all:$(OUT_OBJ)


$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OUT_OBJ)
	