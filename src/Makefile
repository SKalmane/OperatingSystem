CC = gcc
CFLAGS=-g

all: shell

dateUtils.h : dateUtils.c

argcAndArgvUtils.h : argcAndArgvUtils.c

MemoryAllocator.o : MemoryAllocator.c

testMemoryAllocator.o : testMemoryAllocator.c MemoryAllocator.h

shell.o : shell.c argcAndArgvUtils.h dateUtils.h MemoryAllocator.h

shell: shell.o argcAndArgvUtils.o dateUtils.o MemoryAllocator.o

test: testMemoryAllocator.o MemoryAllocator.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o shell test
