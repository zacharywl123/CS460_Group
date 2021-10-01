#include "client.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int main() {
    char input[100];                    // buffer for user input
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char c;
    int inputNum, result;
    
    printf("3A+1 client\n");
    
    // create an unnamed socket, and then name it
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // create addr struct
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    // connect to server socket
    if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
        perror("Error connecting to server!\n");
        exit(EXIT_FAILURE);
    }

    printf("Input Number: ");
    // read string
    fgets(input, sizeof(input), stdin);
    if (sscanf(input, "%d", &inputNum) != 1){
        perror("\nError reading input, exit");
    } else if (inputNum < 1){
        printf("\nNo valid number, exit\n");
    } else {

        printf("\nInput: %d\n", inputNum);

        inputNum = htonl(inputNum);

        write(client_socket, &inputNum, sizeof(int));

        read(client_socket, &result, sizeof(int));

        //printf("\nNumber of steps: %d\n", result);

        result = ntohl(result);

        printf("\nNumber of steps: %d\n", result);
    }
        
    return EXIT_SUCCESS;
}

