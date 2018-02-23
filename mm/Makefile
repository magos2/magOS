SRC= $(wildcard *.c) 
OBJ= $(SRC:.c=.o) 

OUT_DIR=../bin/mm
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ))

all:$(OUT_OBJ)

$(OUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -f $(OUT_OBJ)
