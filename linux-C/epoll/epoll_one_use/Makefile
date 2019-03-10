ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(SRC) && gcc epoll_one_use.c ds_socket.c  -o epoll_one_use  -I$(HEAD)
	@mv $(SRC)/epoll_one_use $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/epoll_one_use
