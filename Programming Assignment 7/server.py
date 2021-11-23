import threading
import socket
import math

HEADER = 64
PORT = 5005
SERVER = "127.0.0.1"
#SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
FORMAT = 'utf-8'
ARITH_OPS = ['+', '-', '*', '/', '^', 'sqrt']

#client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client = socket.socket(socket.AF_INET, # Internet
                       socket.SOCK_DGRAM) # UDP
client.bind(ADDR)


# given protocol code conduct math operation
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
                output_num = num_1 / num_2
            
            elif operator == '^':
                output_num = num_1 ** num_2
        
        output = str(output_num)

    return output


# sends the result to the client
def send_result(addr, result):
    result = result.encode(FORMAT)
    result_length = len(result)
    send_length = str(result_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))
    client.sendto(send_length, addr)
    client.sendto(result, addr)


def start():
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:

        message_length, cli_addr = client.recvfrom(HEADER)
        message_length = message_length.decode(FORMAT)

        if int(message_length) > 0:
            message_length = int(message_length)
            message, cli_addr = client.recvfrom(message_length)
            message = message.decode(FORMAT)
            
            print(f"[{cli_addr}]  Input: {message}")
            result = conduct_operation(message)
            print(f"[{cli_addr}] Result: {result}")
            send_result(cli_addr, result)
            message_length = 0

if __name__ == "__main__":
    print ("[STARTING] server is starting ... ")
    start()