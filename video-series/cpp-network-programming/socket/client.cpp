/*
    client.cpp
    used as stream socket on client
*/

# include <stdio.h>
# include <string>
# include <unistd.h>
# include <stdlib.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>

int main(int argc, char *argv[]) 
{
    // prerequisite
    if (argc != 3) 
    {
        printf("Using:./client ip port\nExample:./client 127.0.0.1 5396\n\n");
        return  -1;
    }

    /* 
        step 1, create a client side stream socket
    */

    // create a file descriptor, everything under UNIX is file. 0:standard input; 1:standard output; 2:standard error
    int clientSockFd;
    if ((clientSockFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)     // -1 is returned if socket initialization failed
    {
        perror("socket");                                           // print fail message to stderr
        return -1;
    }

    /* 
        step 2, connect to server
    */

    // struct for [host entry], including name, alias, host address type, host address length and addrest list, included in <netdb.h>
    // the use of address list is because of an host may have multiple address if it is using multiple NICs
    struct hostent *host;
    /*
        // Structures returned by network data base library
        // All addresses are supplied in host order, and returned in network order (suitable for use in system calls).
        struct hostent {
            char	*h_name;	            // official name of host,   like www.apple.com.cn
            char	**h_aliases;	        // alias list,              like www.apple.cn, etc
            int	    h_addrtype;	            // host address type,       like AF_INET, AF_INET6
            int	    h_length;	            // length of address,       like 4/16 bytes for AF_INET/AF_INET6
            char	**h_addr_list;	        // list of addresses from name server,  like 61.135.169.121, 61.135.169.125, etc, load balancing
        #if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
        #define	h_addr	h_addr_list[0]	    // address, for backward compatibility
        #endif                              // (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE)
        };
    */

    // get host data (...) by domain name
    if ((host = gethostbyname(argv[1])) == 0)
    {
        printf("gethostbyname failed.\n");
        close(clientSockFd);
        return -1;
    }
    /*
        gethostbyname()
        function:   get host data (...) by domain name, included in <netdb.h>
        prototype:  struct hostent *gethostbyname(const char *);
    */

    // struct for server side address, including protocol, port, ip, etc
    struct sockaddr_in servaddr;

    // initialize memory area assigned to &servaddr with sizeof(servaddr) to 0
    memset(&servaddr, 0, sizeof(servaddr));

    // protocol, AF_INET is used here
    servaddr.sin_family = AF_INET;

    // port, specify a port on server for client to connect
    servaddr.sin_port = htons(atoi(argv[2]));

    // ip, 
    memcpy(&servaddr.sin_addr, host->h_addr, host->h_length);
    /*
        memcpy()
        function:   specified memory area copy, copy src with sizeof(src) to dst on memory, included in <string.h>
        prototype:  void *memcpy(void *__dst, const void *__src, size_t __n);
                    dst: destination memory location
                    src: source memory location
                    n:   length of src to be copied

        https://blog.csdn.net/qq_26747797/article/details/82794333 
    */

    // connect
    if (connect(clientSockFd, (struct sockaddr *) &servaddr, sizeof(servaddr)) != 0)    // -1 is returned if connection failed, 0 otherwise
    {
        perror("connect");                                                              // print fail message to stderr
        close(clientSockFd);
        return -1;
    }
    /*
        connect()
        function:   connect to address (servaddr) using client socket file descriptor
        prototype:  int connect(int, const struct sockaddr *, socklen_t) __DARWIN_ALIAS_C(connect);
    */
}
