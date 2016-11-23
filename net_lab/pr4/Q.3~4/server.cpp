//server2.c

#include "header.h"

int main()
{
    struct sockaddr_in serverSocket;
    int serverSocketFD;
    int versionSelect;
    
    
    printf("select '1' or '2': ");
    scanf("%d", &versionSelect);
    if(versionSelect != 1 && versionSelect != 2)
    {
        fprintf(stderr, "select '1' or '2'!\n");
        return 1;
    }
    
    serverSocketFD = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&serverSocket, 0, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);
    serverSocket.sin_port = htons(PORT);
    
    if (bind(serverSocketFD, (struct sockaddr *) &serverSocket, sizeof(serverSocket)) == -1)
    {
        printf("Can not bind.\n");
        return -1;
    }
    
    printf("Waiting for clients...\n");
    
    int readBytes;
    char sendBuffer[BUFFER_SIZE];
    
    while (1)
    {
        struct sockaddr_in information_of_sender;
        socklen_t size_of_information_of_sender = sizeof(information_of_sender);
        
        switch(versionSelect)
        {
            case 1:
                //empty
                break;
                
            case 2:
                recvfrom(serverSocketFD, sendBuffer, sizeof(sendBuffer), 0, (struct sockaddr *)&information_of_sender, &size_of_information_of_sender);
                sendto(serverSocketFD, sendBuffer, strlen(sendBuffer), 0, (struct sockaddr *)&information_of_sender, size_of_information_of_sender);
                break;
                
            default:
                break;
        }
    }
    
    close(serverSocketFD);
    
    return 0;
}
