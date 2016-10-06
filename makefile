CC			=	gcc
CFLAGS	=	-std=c99 -pedantic -Wall -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -g

all: stegit.o
	$(CC) $(CFLAGS) -o stegit stegit.o

stegit.o: stegit.c
	$(CC) $(CFLAGS) -c stegit.c

clean:
	rm -R *.o
