
CC=gcc
CFLAGS=-I. -Wall -g 
DEPS=basicdatastruct.h
OBJ=queue.o stack.o hashtable.o linkedlist.o
LNAME=libdatastruct.a
EXE=queue hashtable stack linkedlist
SRCS=queue.c hashtable.c stack.c linkedlist.c test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

$(LNAME) : $(OBJ)  ;  ar rcs $@ $^ 

clean: ; rm -f $(OBJ) $(LNAME) $(EXE)

hashtable: hashtable.c $(DEPS) ; gcc -o $@ $< $(CFLAGS)

linkedlist: linkedlist.c $(DEPS) ; gcc -o linkedlist $<  $(CFLAGS)

test: $(SRCS) $(DEPS) $(LNAME) ; gcc -o $@ test.c -ldatastruct -L.

.PHONY: clean
