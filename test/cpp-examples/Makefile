SRC_C= $(wildcard *.c) 
SRC_CPP= $(wildcard *.cpp) 
BIN= $(SRC_C:.c=.bin) $(SRC_CPP:.cpp=.bin)

OUT_DIR=./bin
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 
OUT_BIN=$(addprefix $(OUT_DIR)/, $(BIN)) 

all:$(OUT_BIN)

INCLUDE= -I./include
ARCH=arm-linux-gnueabihf
AS=$(ARCH)-as
LD=$(ARCH)-ld
CC=$(ARCH)-gcc 
CFLAGS=-Wall -g -O0 -std=c11 $(INCLUDE)
CCC=$(ARCH)-g++ 
CCFLAGS=-Wall -g -O1 -std=c++11 $(INCLUDE)

$(OUT_DIR)/%.bin:%.cpp
	$(CCC) $(CCFLAGS) $< -o $@
	cp $@ /usr/local/bin
	chmod +x /usr/local/bin/*
	
$(OUT_DIR)/%.bin:%.c
	$(CC) $(CFLAGS) $< -o $@
	cp $@ /usr/local/bin
	chmod +x /usr/local/bin/*
	
clean:
	rm -f $(OUT_BIN)
	
	
