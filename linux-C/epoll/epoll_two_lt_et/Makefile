ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
LIB       = $(ROOTPATH)/lib
BIN       = $(ROOTPATH)/bin

all:
	@cd $(SRC) && gcc epoll_use_two_lt_et.c ds_socket.c ds_tools.c -o epoll_use_two_lt_et  -I$(HEAD)
	@mv $(SRC)/epoll_use_two_lt_et $(BIN)
	@echo "compile complet.........."

.PHONY:clean
clean:
	@rm -fr $(BIN)/epoll_use_two_lt_et
	@echo "make clean  success"
