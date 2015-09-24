
CC=gcc
CFLAGS=-I. -Wall -g 
DEPS=basicdatastruct.h
OBJ=queue.o stack.o hashtable.o linkedlist.o
LNAME=libdatastruct.a
TESTEXE=test
SRCS=queue.c hashtable.c stack.c linkedlist.c test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

$(LNAME) : $(OBJ)  ;  ar rcs $@ $^ 

clean: ; rm -f $(OBJ) $(LNAME) $(TESTEXE)

hashtable: hashtable.c $(DEPS) ; gcc -o $@ $< $(CFLAGS)

linkedlist: linkedlist.c $(DEPS) ; gcc -o linkedlist $<  $(CFLAGS)

$(TESTEXE): $(SRCS) $(DEPS) $(LNAME) ; gcc -o $@ $@.c -ldatastruct -L. #; ./$(TESTEXE)

.PHONY: clean
