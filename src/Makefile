CFLAGS=-g

all: shell

dateUtils.h : dateUtils.c

argcAndArgvUtils.h : argcAndArgvUtils.c

shell.o : shell.c argcAndArgvUtils.h dateUtils.h

shell: shell.o argcAndArgvUtils.o dateUtils.o

clean:
	rm -f *.o shell
