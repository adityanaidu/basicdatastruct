
CC=gcc
CFLAGS=-I. -Wall -g
DEPS=basicdatastruct.h
OBJ=queue.o stack.o hashtable.o
LNAME=libdatastruct.a

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

$(LNAME) : $(OBJ)  ;  ar rcs $@ $^ 

clean: ; rm -f $(OBJ) $(LNAME)

hashtable: hashtable.c $(DEPS) ; gcc -o hashtable $<  $(CFLAGS)

.PHONY: clean
