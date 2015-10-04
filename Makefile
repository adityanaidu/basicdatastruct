
CC=gcc
CFLAGS=-I. -Wall -g -std=c99 -pedantic
DEPS=basicdatastruct.h
OBJ=bds_queue.o bds_stack.o bds_hashtable.o bds_linkedlist.o bds_pqueue.o
BDSLIB=libbasicdatastruct.a
TESTEXE=bds_test
SRCS=bds_queue.c bds_hashtable.c bds_stack.c bds_linkedlist.c bds_pqueue.c bds_test.c

%.o: %.c $(DEPS) ;   $(CC) -c -o $@ $< $(CFLAGS)

clean: ; rm -f $(OBJ) $(BDSLIB) $(TESTEXE)

$(BDSLIB) : $(OBJ)  ;  ar rcs $@ $^ 

$(TESTEXE): $(SRCS) $(DEPS) $(BDSLIB) ; gcc -o $@ $@.c -lbasicdatastruct -L. #; ./$(TESTEXE)

.DEFAULT_GOAL := $(BDSLIB)

.PHONY: clean
