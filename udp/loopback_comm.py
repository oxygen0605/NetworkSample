import socket
import threading
from collections import deque
from time import time, sleep


M_SIZE = 1024
snd_q = deque()
stop = False
lock = threading.Lock()

serv_address = ("127.0.0.1", 1990)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(serv_address)
sock.settimeout(10) # timeout 10秒

def rx_func():
    global M_SIZE, sock, lock,stop
    
    while True:
        sleep(0.1)
        print(stop)
        if stop: break
        
        rx_message, addr = sock.recvfrom(M_SIZE)
        
        print(rx_message)
        if len(snd_q):
            lock.acquire()
            t, m = snd_q.popleft()
            lock.release()
            print("delete: "+m)



rx = threading.Thread(name="rx", target=rx_func)
rx.start()

def tx_func(m):
    global sock, lock, serv_address
    send_len = sock.sendto(m.encode("utf-8"), serv_address)
    lock.acquire()
    snd_q.append([time(), message])
    lock.release()

sleep(10)

while True:
    for i in range(3):
        message = "hello world "+str(i)
        tx_func(message)
        print("sent: "+message)
        sleep(1)
        
    if 0 == len(snd_q): break
    
    if time()-snd_q[0][0] >= 3:
        for i in range(len(snd_q)):
            t, m = snd_q.popleft()
            tx_func(message)
            print("retry: "+m)
            sleep(1)

stop = True
print(stop)
rx.join()
sock.close()