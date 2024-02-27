import socket
import datetime
import time

def initiateClockServer():
    s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Socket created successfully")
    port=8012
    host=socket.gethostname()
    s.bind((host,port))
    s.listen(5)
    print("Socket is listening")
    
    while True:
        conn,addr=s.accept()
        print("Server connected to ",addr)
        conn.send(str(datetime.datetime.now()).encode())
        conn.close()


if __name__=='__main__':
    initiateClockServer()