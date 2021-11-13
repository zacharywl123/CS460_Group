import socket

HEADER = 64
PORT = 5050
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "!DISCONNECT"
SERVER = "127.0.1.1"
ADDR = (SERVER, PORT)
ARITH_OPS = ['+', '-', '*', '/']


# function that converts a math opertion in a string into a protocol string for the serer
def operation_to_protocol(op_str):
    output = 'Invalid'
    input_lst = op_str.split()
    possible_pwr = list(input_lst[0])

    # if first and last args are numbers
    if input_lst[0].isnumeric() and input_lst[2].isnumeric():
        # if the middle item is a valid operator then
        if input_lst[1] in ARITH_OPS:
            output = input_lst[1] + '_' + input_lst[0] + '_' + input_lst[2]
    
    # if follows sqrt of format
    elif input_lst[0] == 'sqrt' and input_lst[1] == 'of' and input_lst[2].isnumeric():
        output = 'sqrt' + '_' + input_lst[2]

    # if has a carrot symbol in argument
    elif '^' in possible_pwr:
        carrot_index = possible_pwr.index('^')
        first_num = input_lst[0][0:carrot_index]
        second_num = input_lst[0][carrot_index+1:]

        #if both arguments on either side of carrot are numbers then valid
        if first_num.isnumeric() and second_num.isnumeric():
            output = '^' + '_' + first_num + '_' + second_num

    return output


output = 'Invalid'
while output == 'Invalid':
    operation = input('Enter in a valid Arithmetic Operation : >>> ')
    output = operation_to_protocol(operation)
    if output == 'Invalid':
        print("Invalid Input Try Again...\n")
    print(f"Protocol Form: '{output}'")
print("VALID OPERATION!")


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
def client_recieve(message):
    message = message.encode(FORMAT)
    message_length = len(message)
    send_length = str(message_length).encode(FORMAT)
    send_length += b' ' * (HEADER - len(send_length))
    client.send(send_length)
    client.send(message)

client_recieve(output)

# op_for_server = '10'.encode(FORMAT)

# client.send(op_for_server)