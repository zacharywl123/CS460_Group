import threading
import socket

host = '127.0.0.1'
port = 59000
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen(5)
clients = []

def broadcast(message):
    for client in clients:
        client.send(message)

# Handles connections from clients 
def handle_client(client):
    while True:
        try:
            message = client.recv(1024)
            broadcast(message)
        except:
            index = clients.index(client)
            clients.remove
            client.close()
            break
# main function to recieve client connections
def receive():
    while True:
        print('Server is running and listening ...')
        client, address = server.accept()
        print(f'Connection is being established with {str(address)}')
        client.send('You are now connected'.encode('utf-8'))
        thread = threading.Thread(target = handle_client, args=(client,))
        thread.start()
if __name__ == "__main__":
    receive()