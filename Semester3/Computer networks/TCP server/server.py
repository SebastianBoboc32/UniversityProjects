import threading
import socket
import json

ADDR = ("0.0.0.0", 5058)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(ADDR)

arrays = []


def mergeSort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        sub_array1 = arr[:mid]
        sub_array2 = arr[mid:]
        mergeSort(sub_array1)
        mergeSort(sub_array2)
        i = j = k = 0
        while i < len(sub_array1) and j < len(sub_array2):
            if sub_array1[i] < sub_array2[j]:
                arr[k] = sub_array1[i]
                i += 1
            else:
                arr[k] = sub_array2[j]
                j += 1
            k += 1
        while i < len(sub_array1):
            arr[k] = sub_array1[i]
            i += 1
            k += 1

        while j < len(sub_array2):
            arr[k] = sub_array2[j]
            j += 1
            k += 1


connected_clients = []
arrays = []


def handle_client(client_socket, addr):
    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            received_data = json.loads(data.decode('utf-8'))
            print(received_data)
            mergeSort(received_data)
            client_socket.send(json.dumps(received_data).encode('utf-8'))
    except Exception as e:
        print(f"Error handling client {addr}: {e}")
    finally:
        client_socket.close()
        connected_clients.remove(client_socket)


def start():
    print(f"Server started on IP: {socket.gethostname()}")
    server_socket.listen()
    while True:
        conn, addr = server_socket.accept()
        print(f"Client {addr} connected succesfully")
        connected_clients.append(conn)
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()


start()
server_socket.close()