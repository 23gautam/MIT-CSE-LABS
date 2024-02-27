import socket
import datetime
from timeit import default_timer as timer

def synchronizeTime():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    port = 8012
    host = socket.gethostname()

    s.connect((host, port))

    request_time = timer()

    # Send a request to the server to get its time
    s.send(b'Requesting server time')

    # Receive server's time and calculate round-trip time
    server_response = s.recv(1024).decode()
    response_time = timer()

    # Server's time is sent as string, convert it to datetime object
    server_time = datetime.datetime.strptime(server_response, "%Y-%m-%d %H:%M:%S.%f")

    # Calculate the round-trip time
    process_delay_latency = (response_time - request_time) / 2

    # Calculate client's synchronized time
    client_time = server_time + datetime.timedelta(seconds=process_delay_latency)

    # Calculate synchronization error
    error = datetime.datetime.now() - client_time

    print("Time returned by server:", server_time)
    print("Process delay latency:", process_delay_latency, "seconds")
    print("Synchronized process client time:", client_time)
    print("Synchronization error:", error.total_seconds(), "seconds")

    s.close()

if __name__ == '__main__':
    synchronizeTime()
