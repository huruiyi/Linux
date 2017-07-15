#create by yekai 20170330

SrcFiles=$(wildcard *.c)

TargetFiles=$(patsubst %.c,%,$(SrcFiles))

all:$(TargetFiles)

%:%.c
	gcc -o $@ $< -g -lpthread

clean:
	-rm -f $(TargetFiles)

