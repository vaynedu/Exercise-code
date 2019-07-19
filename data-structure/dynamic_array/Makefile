ROOT  = $(shell pwd)
HEAD  = $(ROOT)/head
SRC   = $(ROOT)/src
LIB   = $(ROOT)/lib
BIN   = $(ROOT)/bin


all:
	@cd $(SRC) && gcc dynamic_array.c tools.c main.c -o main -I$(HEAD)
	@mv $(SRC)/main $(BIN)
	@echo "compile  complete......"

.PHONY:clean
clean:
	rm -fr $(BIN)/main
