/*
    server.cpp
    used as stream socket on server
*/

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>

int main(int argc, char *argv[]) 
{
    // prerequisite
    if (argc != 2) {
        printf("Using:./server port\nExample:./server 5396\n\n");
        return -1;
    }

    /* 
        step 1, create a server side stream socket 
    */

    // create a file descriptor, everything under UNIX is file. 0:standard input; 1:standard output; 2:standard error
    int serverSocketFileDescriptor;
    if ((serverSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)     // -1 is returned if socket initialization failed
    {
        perror("socket");                                           // print fail message to stderr
        return -1;
    }
    /*
        socket()
        function:   initialize a socket with given network protocol, socket type and socket protocol, included in <socket.h>
        prototype:  int socket(int, int, int);
                    1: network protocol,    AF_INET (TCP/IP – IPv4), AF_INET6 (TCP/IP – IPv6)
                    2: socket type,         SOCK_STREAM (TCP stream), SOCK_DGRAM (UDP datagram), SOCK_RAW (raw socket)
                    3: socket protocol,     set to 0 if domain and type is fixed (not using SOCK_RAW in socket type)

        perror()
        function:   output a descriptive message to stderr, with ": " appends to the tail of the message, included in <stdio.h>
        prototype:  void perror(const char *str) 
        example:    perror("xxx");      // the output will be: "xxx: "
    */

    /* 
        step 2, bind ip & port on socket
    */ 

    // struct for server side address, including protocol, port, ip, etc
    struct sockaddr_in serverAddress;
    /*
        // Socket address, internet style.
        struct sockaddr_in {
            __uint8_t       sin_len;        // ?
            sa_family_t     sin_family;     // network protocol
            in_port_t       sin_port;       // port
            struct  in_addr sin_addr;       // ip
            char            sin_zero[8];    // ?
        };

        // network protocol
        // unsigned(__u) int(int) with 1 bytes(8 bits) defined(_t) in tpyedef
        // range [0, 255] * 1, like 2 -> 00000010
        typedef __uint8_t   sa_family_t;

        // port
        // unsigned(__u) int(int) with 2 bytes(16 bits) defined(_t) in tpyedef
        // range [0, 65535] * 1, like 5396 -> 00010101 00010100
        typedef __uint16_t  in_port_t;

        // ip
        // Internet address (a structure for historical reasons)
        struct in_addr {
            in_addr_t s_addr;
        };

        // ip
        // base type for internet address
        typedef __uint32_t      in_addr_t;      

        // ip
        // unsigned(__u) int(int) with 4 bytes(32 bits) defined(_t) in tpyedef
        // range [0, 255] * 4, like 192.168.0.1 -> 11000000.10101000.00000000.00000001
        typedef unsigned int    __uint32_t;
    */

    // initialize memory area assigned to &serverAddress (a pointer is used here) with sizeof(serverAddress) to 0, 
    memset(&serverAddress, 0, sizeof(serverAddress));
    /*
        memset()
        function:   specified memory area initialization, included in <string.h>
        prototype:  void *memset(void *__b, int __c, size_t __len);
                    s: can be a array (which is a pointer), or just a pointer points to a memory address (like struct)
                    c: is the value to fill in, most used is 0 or -1
                    l: is the number of bytes to fill in with, operated byte-wise
        example 1:  char s[8];
                    memset(s, 0, 8);    // correct use
                                        // each char takes 1 byte, and is filled with 0s for all 8 bits
        example 2:  int n[8];
                    memset(n, 1, 8);    // incorrect use
                                        // 1 int takes 4 bytes (32 bits)
                                        // but we have 8 ints, which takes 32 bytes (128 bits)
                    memset(n, 1, 32);   // incorrect use
                                        // the length has be corrected to 32, but because of byte-wise operation
                                        // the results will be: 
                                        // 0x00000001 00000001 00000001 00000001, which is 16843009 for all 8 ints
                    memset(n, 0, 32);   // correct use, the results will be 0s
                    memset(n, -1, 32);  // correct use, the results will be -1s

        https://www.cnblogs.com/yhlboke-1992/p/9292877.html 
    */

    // protocol, the only protocol for socket is AF_INET/AF_INET6
    serverAddress.sin_family = AF_INET;
    /*
        #define AF_INET 2       //internetwork: UDP, TCP, etc. 
    */

    // ip, any server ip address is allowed (if server has multiple NICs)
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // serverAddress.sin_addr.s_addr = inet_addr("192.168.0.1");     // specific server ip address is allowed
    /*
        // 
        # define INADDR_ANY     (u_int32_t)0x00000000

        // 
        typedef unsigned int    u_int32_t;

        htonl()     host(h) to(to) network(n) long(l)
        function:   transform a unsigned long (host byte order) into big-endian mode (network byte order), included in <arpa/inet.h>
        prototype:  uint32_t htonl(uint32_t hostlong);

        inet_addr()
        function:   transform a decimal ip address into a binary ip address under network byte order in long, included in <inet.h>
        prototype:  in_addr_t inet_addr(const char *);

        // ip
        // base type for internet address
        typedef __uint32_t      in_addr_t; 
    */

    // port, specify a port on server for incoming connection
    serverAddress.sin_port = htons(atoi(argv[1])); 

    // bind ip, port and sizeof(serverAddress) on socket file descriptor (serverSocketFileDescriptor)
    if (bind(serverSocketFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) != 0)   // -1 is returned if socket binding failed, 0 otherwise
    {
        perror("bind");                                                             // print fail message to stderr
        close(serverSocketFileDescriptor);
        return -1;
    }
    /*
        // [XSI] Structure used by kernel to store most addresses.
        struct sockaddr {
            __uint8_t       sa_len;         // total length
            sa_family_t     sa_family;      // [XSI] address family
            char            sa_data[14];    // [XSI] addr value (actually larger)
        };

        atoi()
        function:   transform a string pointed by str into a int, included in <stdlib.h>
        prototype:  int atoi(const char *str)
        example:    atoi("123");        // transform char *str "123" into int 123, 0 is returned if transform failed

        htons()     host(h) to(to) network(n) short(s)
        function:   transform a unsigned short (host byte order) into big-endian mode (network byte order), included in <arpa/inet.h>
        prototype:  uint16_t htons(uint16_t hostshort);

        bind()
        function:   bind ip and port (addr) with size (addrlen) on socket (sockfd), included in <socket.h>
        prototype:  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    */

    /*
        step 3, set socket on listen mode
    */

    // set socket on listen mode
    if (listen(serverSocketFileDescriptor, 5) != 0) 
    {
        perror("listen");
        close(serverSocketFileDescriptor);
        return -1;
    }

    /* 
        step 4, accept client's connection
    */

    // accept client's connection
    int clientSocketFileDescriptor;                 // client side socket
    int socklen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddress;               // client side address
    clientSocketFileDescriptor = accept(serverSocketFileDescriptor, (struct sockaddr *) &clientAddress, (socklen_t *) &socklen);
    printf("client (%s) connected.\n", inet_ntoa(clientAddress.sin_addr));

    /*
        step 5, communicate with client, accept data and return ok
    */

    // communicate with client, accept data and reply ok
    char buffer[1024];
    while (true)
    {
        int iret;
        memset(buffer, 0, sizeof(buffer));

        if ((iret = recv(clientSocketFileDescriptor, buffer, sizeof(buffer), 0)) <= 0)  // accepting data from client
        {
            printf("iret = %d\n", iret);
            break;
        }
        printf("accepting: %s\n", buffer);

        strcpy(buffer, "ok");
        if ((iret = send(clientSocketFileDescriptor, buffer, strlen(buffer), 0)) <= 0)  // sending replies to client
        {
            perror("send");
            break;
        }
        printf("sending: %s\n", buffer);
    }

    /*
        step 6, close sockets, release resource
    */

    // close sockets, release resource
    close(serverSocketFileDescriptor);
    close(clientSocketFileDescriptor);
}
