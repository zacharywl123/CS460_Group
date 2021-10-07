CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -pthread -Wall -std=c99 -pedantic $(DEBUG)

all: client server

client : client.o threadpool.o
	$(CC) $(LFLAGS) client.o threadpool.o -o client

client.o : client.c client.h threadpool.h dbg.h
	$(CC) $(CFLAGS) client.c

server : server.o
	$(CC) $(LFLAGS) server.o -o server

server.o : server.c server.h
	$(CC) $(CFLAGS) server.c

threadpool.o: threadpool.c threadpool.h dbg.h
	$(CC) $(CFLAGS) threadpool.c

clean:
	\rm *.o client