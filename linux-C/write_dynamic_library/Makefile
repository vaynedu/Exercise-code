ROOTPATH   =  $(shell pwd)
SRC        =  $(ROOTPATH)/src
LIB        =  $(ROOTPATH)/lib
BIN        =  $(ROOTPATH)/bin



all : collect
	@cd $(SRC) && $(CC) mysort.c -o mysort  -lquick_sort  -L$(LIB)
	@mv $(SRC)/mysort $(BIN)
	@echo "compiled....."
collect:
	@cd $(SRC) && $(CC) -shared -fpic quick_sort.c -o libquick_sort.so
	@mv $(SRC)/libquick_sort.so $(LIB)
	/sbin/ldconfig  $(LIB)

.PHONY:clean
clean:
	@cd $(LIB) && rm -fr libquick_sort.so
	@rm -fr $(BIN)/mysort
