
CC=gcc
CFLAGS=-I. -Wall -g 
DEPS=basicdatastruct.h
OBJ=bds_queue.o bds_stack.o bds_hashtable.o bds_linkedlist.o
STATLIB=libdatastruct.a
TESTEXE=bds_test
SRCS=bds_queue.c bds_hashtable.c bds_stack.c bds_linkedlist.c bds_test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

clean: ; rm -f $(OBJ) $(STATLIB) $(TESTEXE)

$(STATLIB) : $(OBJ)  ;  ar rcs $@ $^ 

$(TESTEXE): $(SRCS) $(DEPS) $(STATLIB) ; gcc -o $@ $@.c -ldatastruct -L. #; ./$(TESTEXE)

.DEFAULT_GOAL := $(STATLIB)

.PHONY: clean
