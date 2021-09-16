#include "server.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    char input[100], buffer[100];       // buffer for user input
    int client_socket, nread;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char c;
    
    printf("Daytime client\n");

    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == 0) {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }
    printf("Made it here \n");
    
    while (TRUE) {
        printf("Enter IP for time: ");
        
        // read string
        fgets(input, sizeof(input), stdin);
        // remove new line char from end of str  
        input[strlen(input)-1] = '\0';

        printf("inputed: %s\n", input);

        printf("pre write\n");
        while ((nread = read(client_socket, buffer, 100)) > 0) {
            buffer[nread] = 0;
            if (fputs(buffer, stdout) == EOF)
            {
                perror("fputs error"); /* write daytime on stdout */
                return -1;
            }
            printf("buffer: %s\n", buffer);
        }
    }
    
    return EXIT_SUCCESS;
}

