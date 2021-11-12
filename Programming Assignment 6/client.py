import threading
import socket
alias = input('Choose an alias : >>> ')
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('127.0.0.1', 59000))
def client_recieve():
    while True:
        try:
            message = client_recv(1024).decode('utf-8')
        except:
            print('Error')
            client.close()
            break