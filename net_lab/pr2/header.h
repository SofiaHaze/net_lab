#ifndef Net02_header_h
#define Net02_header_h

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# define PORT 10003
# define BUFFER_SIZE 100

ssize_t readvn(int socketFD, char* buffer, size_t maxLength);
ssize_t writevn(int socketFD, char* buffer, size_t length);

#endif

