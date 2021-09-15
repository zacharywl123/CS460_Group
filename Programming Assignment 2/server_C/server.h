/************************************************************************
 * libraries
 ************************************************************************/

// should always be there ...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// socket/bind/listen/accept
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// read/write/close
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>

// I ADDED THIS STATEMENT (ECB)
#include <signal.h>

// multithreading
#include <pthread.h>

/************************************************************************
 * function prototype declarations
 ************************************************************************/
void *handle_client(void *client_socket_void);

/************************************************************************
 * preprocessor directives
 ************************************************************************/
#define SERVER_ADDR "127.0.0.1" // loopback ip address
// #define SERVER_ADDR "time.nist.gov" // loopback ip address
#define PORT 8800             // port the server will listen on

// I cannot let go of the old-fashioned way :) - for readability ...
#define FALSE false
#define TRUE !false

// number of pending connections in the connection queue
#define NUM_CONNECTIONS 1
