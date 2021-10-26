# socket (c/s)
# https://www.freecplus.net/0047ac4059b14d52bcc1d4df6ae8bb83.html

# socket提供了stream（流）和datagram（数据报）两种通信机制。
# stream socket基于TCP协议，是一个有序、可靠、双向字节流的通道，传输数据不会丢失，不会重复，不会乱序。
# datagram socket基于UDP协议，不需要建立和维持链接，但可能出现丢失和乱序的问题。UDP是不可靠协议，对数据的长度也有限制，但是效率较高。
# 举例：实时音视频聊天可能采用UDP协议，因为该类型业务可以接受一定程度的数据丢失，且不必重传。
# 注：因datagram socket应用场景范围有限，故本教程仅针对stream socket。

# basic socket connection sequence
# client side                                           # server side
socket()        # create a stream socket                socket()            # create a stream socket
                                                        bind()              # bind ip & port for socket 
                                                        listen()            # set socket on listen mode
connect()       # send connection request               accept()            # accept connection request
send()/recv()   # send/receive data         < ---- >    recv()/send()       # receive/send data
close()         # close socket connection               close()             # close socket connection

