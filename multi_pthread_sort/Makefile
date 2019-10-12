ROOTPATH  = $(shell pwd)
SRC       = $(ROOTPATH)/src
HEAD      = $(ROOTPATH)/head
BIN       = $(ROOTPATH)/bin

all :
	@echo "Makefile  is compiling......" 
	@cd $(SRC) && $(CC) multi_pthread_sort.c -o multi_pthread_sort -lpthread -I$(HEAD)
	@mv $(SRC)/multi_pthread_sort $(BIN)
	@echo "Makefile  is completed....."
.PHONY:clean
clean:
	@rm -fr $(BIN)/multi_pthread_sort
	@echo "clean succeed"
