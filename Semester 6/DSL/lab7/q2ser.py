import socket
import datetime
import time

def synchronize_time(conn):
    client_request_time = datetime.datetime.now()
    conn.send(str(client_request_time).encode())

def initiateClockServer():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Socket created successfully")
    port = 8012
    host = socket.gethostname()
    s.bind((host, port))
    s.listen(5)
    print("Socket is listening")
    
    while True:
        conn, addr = s.accept()
        print("Server connected to ", addr)
        synchronize_time(conn)
        conn.close()

if __name__ == '__main__':
    initiateClockServer()
