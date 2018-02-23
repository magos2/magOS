EXE=janin
SRC= $(wildcard *.cpp) 
OBJ= $(SRC:.cpp=.o)


OUT_DIR=../bin/jvm
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 

all:$(OUT_DIR)/$(EXE)

INCLUDE= -I./include
#GCC_INCLUDE=-I/usr/lib/gcc/i686-redhat-linux/4.4.7/include
AS=as
LD=ld
CC=g++ 
CFLAGS=-Wall -g -std=c++11 $(INCLUDE) $(GCC_INCLUDE)
LDFLAGS=

$(OUT_DIR)/%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


$(OUT_DIR)/$(EXE):$(OUT_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@
	cp $@ /usr/local/test/
	chmod +x /usr/local/test/$(EXE)
	
init:
	mkdir -p $(OUT_DIR)
	
clean:
	rm -f $(OUT_DIR)/$(EXE) $(OUT_OBJ)
	
	
	