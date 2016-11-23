//client.cpp
# include "header.h"


int main(){
    struct sockaddr_in serverAddress,clientAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    inet_aton("127.0.0.1", (struct in_addr*) &serverAddress.sin_addr.s_addr);
    serverAddress.sin_port = htons(PORT);
    
    // 소켓을 생성하시오.
    int connectFD = socket(AF_INET, SOCK_DGRAM,0); // SOCK_STREAM: TCP, SOCK_DGRAM: UDP
    
    int readBytes, sentBytes;
    char sendBuffer[BUFFER_SIZE];
    char receiveBuffer[BUFFER_SIZE];
    
    while(true){
        
        memset(sendBuffer, 0, sizeof(BUFFER_SIZE));
        memset(receiveBuffer, 0, sizeof(BUFFER_SIZE));
        
        printf("(press q to exit) Input:");
        
        gets(sendBuffer);
        
        if(sendBuffer[0]=='q'){
            printf("wait.. to exit \n");
            break;
        }
        
        //sendto =Write  sendBuffer에 저장 되어있는 데이터를 buffer_size만큼 connectFD를 통해서 서버주소로 보냄 ~ :) 그리고 보낸 크기 만큼 serverAddress에 저장하는 듯 ?!
        sentBytes = sendto(connectFD, sendBuffer, BUFFER_SIZE, 0, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
        
        if (sentBytes <= 0) {
            printf("Write error\n");
            fflush(stdout);
            break;
        }
        
        fflush(stdout);
        printf("Bro !! Successfully ur message(%d Bytes) is sent to server \n",sentBytes);
        fflush(stdout);
        
        socklen_t clientAddressLength=sizeof(clientAddress);
        readBytes = recvfrom(connectFD,receiveBuffer, BUFFER_SIZE, 0, (struct sockaddr*) &clientAddress, &clientAddressLength);
        
        if (readBytes <= 0) {
            printf("Read error\n");
            fflush(stdout);
            break;
        }
        
        printf("client: %s\n",receiveBuffer);
        fflush(stdout);
        
    }
    
    // 소켓을 close 하시오.
    close(connectFD);
    return 0; }