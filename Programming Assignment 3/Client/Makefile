CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -pedantic -c $(DEBUG)
LFLAGS = -Wall -std=c99 -pedantic $(DEBUG)

client : client.o
	$(CC) $(LFLAGS) client.o -o client

client.o : client.c client.h
	$(CC) $(CFLAGS) client.c

clean:
	\rm *.o