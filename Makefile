
CC=gcc
CFLAGS=-c -I. -Wall -Wextra -g -std=c99 -pedantic
DEPS=basicdatastruct.h
OBJ=bds_queue.o bds_stack.o bds_hashtable.o bds_linkedlist.o bds_pqueue.o bds_bst.o
BDSLIB=libbasicdatastruct.a
TESTEXE=bds_test
SRCS=bds_queue.c bds_hashtable.c bds_stack.c bds_linkedlist.c bds_pqueue.c bds_test.c bds_bst.c

%.o: %.c $(DEPS) ;   $(CC) -o $@ $< $(CFLAGS)

clean: ; rm -f $(OBJ) $(BDSLIB) $(TESTEXE)

$(BDSLIB) : $(OBJ)  ;  ar rcs $@ $^ 

$(TESTEXE): $(SRCS) $(DEPS) $(BDSLIB) ; gcc -o $@ $@.c -lbasicdatastruct -L. #; ./$(TESTEXE)

.DEFAULT_GOAL := $(BDSLIB)

.PHONY: clean
