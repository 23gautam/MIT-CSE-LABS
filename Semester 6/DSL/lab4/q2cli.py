import socket as s

clisocket=s.socket(s.AF_INET,s.SOCK_DGRAM)
host='172.16.59.27'
port=9999

print("Do Ctrl+c to exit the program !!")

while True:
	msg=input(str("Type some text to send => "))
	clisocket.sendto(msg.encode(),(host,port))
	print("Client Sent: ",msg)
	data,addr=clisocket.recvfrom(1024)
	print("Client Received: ",data.decode())

clisocket.close()