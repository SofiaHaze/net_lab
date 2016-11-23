
#include "header.h"
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define TIMEOUT 5

void alarmHandler(int sig);
void err_sys(const char * str);

int main(int argc, char * * argv)
{
    signal(SIGALRM, alarmHandler);
    
    if (argc != 2) {
        printf("Usage: %s IPv4-address\n", argv[0]);
        return -1;
    }
    
    struct sockaddr_in serverSocket;
    int clientSocketFD = socket(AF_INET, SOCK_DGRAM, 0);
    int readBytes;
    char sendBuffer[BUFFER_SIZE];
    char receiveBuffer[BUFFER_SIZE];
    socklen_t serverSocketSize = sizeof(serverSocket);
    
    //information if server's socket
    memset(&serverSocket, 0, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    inet_aton(argv[1], (struct in_addr *) &serverSocket.sin_addr.s_addr);
    serverSocket.sin_port = htons(PORT);
    
    while(1)
    {
        //get a string from user
        printf("Input a string: ");
        fgets(sendBuffer, sizeof(sendBuffer) , stdin);
        if(sendBuffer[strlen(sendBuffer) - 1] == '\n')
            sendBuffer[strlen(sendBuffer) - 1] = '\0';
        
        sendto(clientSocketFD, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *)&serverSocket, serverSocketSize);
        
        //alarm!!
        alarm(TIMEOUT);
        
        if((readBytes = recvfrom(clientSocketFD, receiveBuffer, strlen(sendBuffer), 0, NULL, NULL)) < 0)
        {
            if(errno == EINTR)
                fprintf(stderr, "socket timeout\n");
            else
                err_sys("recvfrom error");
        }
        else
        {
            //successfully received from echo server
            //reset alarm
            alarm(0);
            receiveBuffer[readBytes] = '\0';
            printf("from echo server: %s\n\n", receiveBuffer);
        }
    }
    
    return 0;
}
void alarmHandler(int sig)
{
    printf("alarm occured!!!\n");
}
void err_sys(const char * str)
{
    perror(str);
    exit(1);
}