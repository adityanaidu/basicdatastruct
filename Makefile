
CC=gcc
CFLAGS=-I. -Wall -g -std=c99 -pedantic
DEPS=basicdatastruct.h
OBJ=bds_queue.o bds_stack.o bds_hashtable.o bds_linkedlist.o bds_pqueue.o
STATLIB=libdatastruct.a
TESTEXE=bds_test
SRCS=bds_queue.c bds_hashtable.c bds_stack.c bds_linkedlist.c bds_pqueue.c bds_test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

clean: ; rm -f $(OBJ) $(STATLIB) $(TESTEXE)

$(STATLIB) : $(OBJ)  ;  ar rcs $@ $^ 

$(TESTEXE): $(SRCS) $(DEPS) $(STATLIB) ; gcc -o $@ $@.c -ldatastruct -L. #; ./$(TESTEXE)

.DEFAULT_GOAL := $(STATLIB)

.PHONY: clean
