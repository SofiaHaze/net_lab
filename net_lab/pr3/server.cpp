//server.cpp

# include "header.h"
int main(){
    struct sockaddr_in serverAddress, clientAddress;
    
    memset(&serverAddress, 0, sizeof(serverAddress));
    memset(&clientAddress, 0, sizeof(clientAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);
    
    socklen_t clientAddressLength;
    
    
    // 서버 소켓을 생성하고 서버 주소와 bind 하시오.
    int connectedFD = socket(AF_INET, SOCK_DGRAM,0); // SOCK_STREAM: TCP, SOCK_DGRAM: UDP
    
 
    //여기서 중요한 것은 sockaadr 을 사용하여 serverAdress를 connectFD에 bind 하는 것이당~~
    //sockaddr을 사용하는 이유는 구조체 (void *)가 없기 떄문~~!
    if(bind(connectedFD, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) == -1)
    {
        printf("bind error");
        return 1;
    }
    
    int readBytes, sentBytes;
    char sendBuffer[BUFFER_SIZE];
    char receiveBuffer[BUFFER_SIZE];
    
    printf("I'm a server running in circles \n");
    fflush(stdout);
    
    while(1){
        
            memset(sendBuffer,0,BUFFER_SIZE);
        memset(receiveBuffer,0,BUFFER_SIZE);
        
        
        //if this is commented write eroor happens !
        clientAddressLength=sizeof(clientAddress);
        
        
         /* sockfd 소켓으로 들어오는 데이터를 받아 recvBuffer에 저장 */
        readBytes=recvfrom(connectedFD,receiveBuffer, BUFFER_SIZE,0,(struct sockaddr*) &clientAddress, &clientAddressLength);
        
        printf("I got a message form clients \n");
        fflush(stdout);
        
        if(readBytes<0){
            printf("Bro What's wrong? client sent wrong message ^^\n");
            fflush(stdout);
            break;
        }
        
        //sprintf(sendBuffer,"%s",receiveBuffer);
        
        sentBytes = sendto(connectedFD, receiveBuffer, BUFFER_SIZE, 0, (struct sockaddr*) &clientAddress, sizeof(clientAddress));
        
        if (sentBytes <= 0) {
            printf("Write error\n");
            fflush(stdout);
            break;
        }
        
    }
    close(connectedFD);
    return 0;
    
    
}