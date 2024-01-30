import socket as s

sock=s.socket(s.AF_INET,s.SOCK_STREAM)

host=s.gethostname()
port=9991

sock.connect((host,port))
tm=sock.recv(1024)
print('Current time from Server:',tm.decode())
sock.close()