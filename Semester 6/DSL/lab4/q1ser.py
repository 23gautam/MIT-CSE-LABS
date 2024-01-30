import socket as s
import time

sersocket=s.socket(s.AF_INET,s.SOCK_DGRAM)

host=s.gethostname()

port=12121

sersocket.bind((host,port))


while True:
	print("Waiting for client..")
	data,addr = sersocket.recvfrom(1024)
	#receive data from client
	print( "Received Messages:",data.decode()," from",addr)
	currentTime=time.ctime(time.time())+"\n"
	sersocket.sendto(currentTime.encode('ascii'),addr)

sersocket.close()
