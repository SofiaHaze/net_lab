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
        
        //클라이언트의 접속 요청을 허가하시오
        int connectFD = accept(listenFD, (struct sockaddr*)&connectSocket, &connectSocketLength);
        
        getpeername(connectFD, (struct sockaddr*)&peerSocket, &connectSocketLength);
        char peerName[sizeof(peerSocket.sin_addr) + 1] = {0};
        
        sprintf(peerName, "%s", inet_ntoa(peerSocket.sin_addr));
        printf("Client : %s\n", peerName);
        
        
        char buffer[BUFFER_SIZE] = {0};
        sprintf(buffer, "Hello\n");
        write(connectFD, buffer, strlen(buffer));
        
        //클라이언트와의 접속을 끊으시오
        close(connectFD);
    }
    //서버용 리슨 소켓을 닫으시오
    //close(listenFD);
    return 0;
    
}