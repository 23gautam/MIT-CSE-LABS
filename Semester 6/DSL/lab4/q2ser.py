import socket as s

sersocket=s.socket(s.AF_INET,s.SOCK_DGRAM)
host=s.gethostname()
port=9999

sersocket.bind((host,port))

print("Do Ctrl+c to exit the program !!")

while True:
	print("####### Server is listening #######")
	data,addr=sersocket.recvfrom(1024)
	print("Server received: ",data.decode())
	msg=input(str("Type some text to send => "))
	sersocket.sendto(msg.encode(),addr)
	print("Server sent : ",msg)

sersocket.close()
