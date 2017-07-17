src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

all: poll_server client

poll_server: poll_server.o wrap.o
	gcc $^ -o $@ -Wall
client: client.o wrap.o
	gcc $^ -o $@ -Wall

%.o:%.c
	gcc -c $< -Wall

.PHONY: clean all
clean: 
	-rm -rf poll_server client $(obj)
