#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 10001
#define BUFFER_SIZE 100

ssize_t readvn(int socketFD, char* buffer, size_t maxLength);
ssize_t writevn(int socketFD, char* buffer, size_t length);
