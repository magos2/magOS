#
# Under Termux(Android), use $HOME as base directory for executables
#
EXE=janin
SRC= $(wildcard *.cpp) 
OBJ= $(SRC:.cpp=.o)


OUT_DIR=../bin/jvm
INSTALL_DIR=$(HOME)/usr/local
OUT_OBJ=$(addprefix $(OUT_DIR)/, $(OBJ)) 

all:$(OUT_DIR)/$(EXE)

INCLUDE= -I./include
AS=as
LD=ld
CC=g++
CFLAGS=-Wall -g -std=c++11 $(INCLUDE) $(GCC_INCLUDE)
LDFLAGS=

$(OUT_DIR)/%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@


$(OUT_DIR)/$(EXE):$(OUT_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@
	cp $@ $(INSTALL_DIR)/bin/
	chmod +x $(INSTALL_DIR)/bin/$(EXE)

init:
	mkdir -p $(INSTALL_DIR)/test
	mkdir -p $(INSTALL_DIR)/bin
	cp ./test/*.class  $(INSTALL_DIR)/test/
  
clean:
	rm -f $(OUT_DIR)/$(EXE) $(OUT_OBJ)
	
	
	