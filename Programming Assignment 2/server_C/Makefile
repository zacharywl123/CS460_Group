CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -pthread -Wall -std=c99 -pedantic $(DEBUG)

all: server daytime_client echo_client

server : server.o
	$(CC) $(LFLAGS) server.o -o server

daytime_client : daytime_client.o
	$(CC) $(LFLAGS) daytime_client.o -o daytime_client

echo_client : echo_client.o
	$(CC) $(LFLAGS) echo_client.o -o echo_client

server.o : server.c server.h
	$(CC) $(CFLAGS) server.c

daytime_client.o : daytime_client.c server.h
	$(CC) $(CFLAGS) daytime_client.c

echo_client.o : echo_client.c server.h
	$(CC) $(CFLAGS) echo_client.c

clean:
	\rm *.o