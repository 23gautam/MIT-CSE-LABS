import socket as s

clisocket=s.socket(s.AF_INET,s.SOCK_DGRAM)
host=s.gethostname()
port=12121

msg="Whats the time"+"\n"
clisocket.sendto(msg.encode(),(host,port))
data,addr=clisocket.recvfrom(1024)
print("Current time from server is: ",data.decode())
clisocket.close()