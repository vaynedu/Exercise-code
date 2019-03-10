ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(SRC) && gcc select_use.c ds_socket.c ds_tools.c -o select_use  -I$(HEAD)
	@mv $(SRC)/select_use $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/select_use
