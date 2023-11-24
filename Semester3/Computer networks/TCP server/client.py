import socket
import json

ADDR = ("0.0.0.0", 5050)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(ADDR)


def communicate():
    while True:
        input_data = input("Type an array of numbers (comma-separated): ")
        if input_data:
            data = [int(x.strip()) for x in input_data.split(",")]
            data_json = json.dumps(data)
            client_socket.send(data_json.encode('utf-8'))
            received_data_json = client_socket.recv(1024).decode('utf-8')
            received_data = json.loads(received_data_json)
            print(f"Sorted data: {received_data}")
        else:
            print("Empty array")
            break


communicate()
client_socket.close()
