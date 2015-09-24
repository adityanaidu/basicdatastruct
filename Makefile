
CC=gcc
CFLAGS=-I. -Wall -g 
DEPS=basicdatastruct.h
OBJ=queue.o stack.o hashtable.o linkedlist.o
STATLIB=libdatastruct.a
TESTEXE=test
SRCS=queue.c hashtable.c stack.c linkedlist.c test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)



clean: ; rm -f $(OBJ) $(STATLIB) $(TESTEXE)

$(STATLIB) : $(OBJ)  ;  ar rcs $@ $^ 

$(TESTEXE): $(SRCS) $(DEPS) $(STATLIB) ; gcc -o $@ $@.c -ldatastruct -L. #; ./$(TESTEXE)

.DEFAULT_GOAL := $(STATLIB)

.PHONY: clean
