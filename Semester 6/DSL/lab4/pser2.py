import socket as s
import time

serversocket=s.socket(s.AF_INET,s.SOCK_STREAM)

host=s.gethostname()

port=9991

serversocket.bind((host,port))

serversocket.listen(5)

while True:
	clientsocket,addr=serversocket.accept()
	print("Got a connection from %s"%str(addr))
	currentTime=time.ctime(time.time())+"\n"
	clientsocket.send(currentTime.encode('ascii'))
	clientsocket.close()