//server.cpp
# include "header.h"
# define LISTEN_QUEUE_SIZE 5
int main() {
    
    
    //서버의 listen 소켓 데이터 구조를 생성하시오
    struct sockaddr_in listenSocket;
    memset(&listenSocket, 0, sizeof(listenSocket));
    listenSocket.sin_family = AF_INET;
    listenSocket.sin_addr.s_addr = htonl(INADDR_ANY );
    listenSocket.sin_port = htons(PORT);
    
    //listen file descriptor를 생성하시오
    int listenFD = socket(AF_INET, SOCK_STREAM, 0);
    
    //bind와 listen을 수행하시오
    if (bind(listenFD, (struct sockaddr *) &listenSocket, sizeof(listenSocket)) == -1) {
        printf("Can't Connect !\n");
        return -1;
    }
    
    if (listen(listenFD, LISTEN_QUEUE_SIZE) == -1) {
        printf("Can't Listen ! \n");
        return -1;
    }
    
    printf("Waiting for clients...\n");
    
    while (1) {
        //클라이언트와 통신할 소켓을 선언하시오
        struct sockaddr_in connectSocket, peerSocket;
        socklen_t connectSocketLength = sizeof(connectSocket);
        
        //클라이언트의 접속 요청을 허가하면 껍데기 connectSocekt 구조체에 클라이언트에 대한 정보들이 들어감
        int connectFD = accept(listenFD, (struct sockaddr*)&connectSocket, &connectSocketLength);
        
        int integer1, integer2, sum;
        int readBytes, writtenBytes;
        char sendBuffer[BUFFER_SIZE];
        char receiveBuffer[BUFFER_SIZE];
        
        while (true) {
        
            memset(sendBuffer, 0, sizeof(BUFFER_SIZE));
            memset(receiveBuffer, 0, sizeof(BUFFER_SIZE));
            
            readBytes = read(connectFD, receiveBuffer, BUFFER_SIZE);
            
            if (readBytes < 0) {
                printf("Read error");
                fflush(stdout);
                break;
            } else if (readBytes == 0) {
                printf("connection with user is closed! \n");
                fflush(stdout);
                break;
            }
            
            sscanf(receiveBuffer, "%d %d", &integer1, &integer2);
            
            sum = integer1 + integer2;
            writtenBytes = sprintf(sendBuffer, "%d", sum);
            writtenBytes = write(connectFD, sendBuffer, sizeof(sendBuffer));
            if (writtenBytes <= 0) {
                printf("Write error");
                break;
            }
        }
        //클라이언트와의 접속을 끊으시오
        close(connectFD);
    }
    //서버용 리슨 소켓을 닫으시오
    close(listenFD);
    return 0;
}