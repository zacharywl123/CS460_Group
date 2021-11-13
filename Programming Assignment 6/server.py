import threading
import socket
import math

HEADER = 64
PORT = 5050
SERVER = "127.0.0.1"
#SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "!DISCONNECT"
ARITH_OPS = ['+', '-', '*', '/', '^', 'sqrt']

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)

server.listen(5)
clients = []


def conduct_operation(input_str):
    output = 'Error'
    input_list = input_str.split('_')
    output_num = 0
    
    if input_list[0] in ARITH_OPS:
        operator = input_list[0]
        num_1 = int(input_list[1])

        if operator == 'sqrt':
            output_num = math.sqrt(num_1)
        else:
            num_2 = int(input_list[2])

            if operator == '+':
                output_num = num_1 + num_2

            elif operator == '-':
                output_num = num_1 - num_2
            
            elif operator == '*':
                output_num = num_1 * num_2
            
            elif operator == '/':
                output_num = num_1 - num_2
            
            elif operator == '^':
                output_num = num_1 ** num_2
        
        output = str(output_num)

    return output


# Handles connections from clients 
def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected")
    connected = True
    while connected:

        message_length = conn.recv(HEADER).decode(FORMAT)

        if message_length:
            message_length = int(message_length)
            message = conn.recv(message_length).decode(FORMAT)

            if message == 'DISCONNECT_MESSAGE':
                connected = False
            
            print(f"[{addr}]  Input: {message}")
            result = conduct_operation(message)
            print(f"[{addr}] Result: {result}")

    conn.close()


def start():
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")

if __name__ == "__main__":
    print ("[STARTING] server is starting ... ")
    start()