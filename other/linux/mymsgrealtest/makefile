# Makefile 
.SUFFIXES:
.SUFFIXES:  .c .o

all: testmsgreal

CC	= gcc

WORKDIR=.
LIBDIR=$(HOME)/lib
LIBS = -L$(LIBDIR) -lmymessagereal
OUTDIR=$(HOME)/bin

INCLDIR=$(WORKDIR)/incl
INCLFLG= -I$(WORKDIR)/incl
CFLAG= $(INCLFLG) -g -c -Wall

VPATH = $(WORKDIR)/src

OBJ1 =keymng_msg_test.o

testmsgreal:$(OBJ1)
	$(CC) $(LIBS) $^ -o $@ 

# 当依赖发生更新时,目标重新生成 (按照规则生成)


#testmsgreal:keymng_msg_test.o 2.o 3.o 
#	gcc  -L/home/it01/lib -lmymessagereal keymng_msg_test 2.o  3.o

#testmsgreal:testkeymngmsg.o testkeymngmsg2.o  testkeymngmsg3.o
#	gcc -L/home/it01/lib -lmymessagereal testkeymngmsg.o testkeymngmsg2.o  testkeymngmsg3.o -o testmsgreal

.c.o:
	$(CC) $(CFLAG) $<
	
#*.o:*.c        3.c
#	$(CC) $(CFLAG) $<	


#*.o:*.c      1.c 2.c 3.c 
#	gcc -I./incl -g -c -Wall $<
	
#	gcc -I./incl -g  1.c   -c 1.o
#	gcc -I./incl -g  2.c   -c 2.o
#	gcc -I./incl -g  3.c   -c 3.o
	
	
.PHONY:clean
clean:
	rm *.o
	rm testmsgreal