CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pedantic $(DEBUG)

all: server client

server : server.o
	$(CC) $(LFLAGS) server.o -o server

client : client.o
	$(CC) $(LFLAGS) client.o -o client

server.o : server.c server.h
	$(CC) $(CFLAGS) server.c

client.o : client.c server.h
	$(CC) $(CFLAGS) client.c

clean:
	\rm *.o server client