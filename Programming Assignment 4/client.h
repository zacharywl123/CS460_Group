#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// turn on debugging
#define DBG
#include "dbg.h"

int three_a_plus_one(int input);
int three_a_plus_one_rec(int input);
void three_a_plus_one_wrapper(void *number_ptr);

#define NUMBER_TASKS 10000
#define SERVER_ADDR "127.0.0.1"
#define PORT 8881

#define FALSE 0
#define TRUE !FALSE