#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    pthread_t p_ids[30];
    int client_socket;
    pthread_mutex_t server_lock;

    // sent when ,client disconnected
    signal(SIGPIPE, SIG_IGN);
    
    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    printf("Server Bound\n");
    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }
    printf("Listened to Socket, awaiting connections...\n");

    pthread_mutex_init(&server_lock, NULL);
    
    // server loop
    while (TRUE) {

        pthread_mutex_lock(&server_lock);
        
        client_socket = accept(server_socket, NULL, NULL);

        for (int p_id = 0; p_id < 30; p_id++){

            pthread_t new_thread;
            p_ids[p_id] = new_thread;

            struct thread_args args;
            args.p_id = p_id;
            args.server_socket = server_socket;

            pthread_create(&new_thread, NULL ,handle_client, (void*) &args);

            // detatch if ready
            pthread_detach(new_thread);

        }

        pthread_mutex_unlock(&server_lock);

    }

    return 1;
}


/************************************************************************
 * handle client
 ************************************************************************/

void *handle_client(void *args) {
    struct thread_args *arguments = (struct thread_args *)args;
    int p_id = arguments->p_id;
    int server_socket = arguments->server_socket;

    int input;
    int keep_going = TRUE;
    int client_socket;
    int num_steps = 0;
    int iterator;
    
    while (keep_going) {

        // accept connection to client
        if ((client_socket = accept(server_socket, NULL, NULL)) == -1) {
            perror("Error accepting client");
        } else {
            printf("\nAccepted client\n");

            read(client_socket, &input, sizeof(int));

            // 3a+1 algorithm
            iterator = input;
            while (iterator != 1){
                num_steps++;
                // if even then divide by 2
                if (iterator % 2 == 0) {
                    iterator /= 2;
                } // if odd the 3a + 1
                else{
                    iterator = iterator*3 + 1;
                }
            }

            write(client_socket, &num_steps, sizeof(int));

        }
    }
    
    // cleanup
    if (close(client_socket) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    } else {
        printf("\nClosed socket to client, exit\n");
    }

    printf("Thread ID %d: input->%d took %d steps", p_id, input, num_steps);

    return 0;
}
