# include "header.h"
int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s IPv4-address\n", argv[0]);
        return -1; }
    
    
    //서버에 접속할 소켓 데이터 구조를 선언하시오
    struct sockaddr_in connectSocket;
    memset(&connectSocket, 0, sizeof(connectSocket));
    connectSocket.sin_family = AF_INET;
    inet_aton(argv[1], (struct in_addr*) &connectSocket.sin_addr.s_addr);
    connectSocket.sin_port = htons(PORT);
    
    
    //connect file descriptor를 선언하시오
    int connectFD = socket(AF_INET, SOCK_STREAM, 0);
    
    
    //서버에 접속하시오
    if (connect(connectFD, (struct sockaddr*) &connectSocket, sizeof(connectSocket)) == -1) {
        printf("Can not connect.\n");
        return -1;
    }
    else {
        int integer1, integer2, inputValid;
        int readBytes, writtenBytes;
        char sendBuffer[BUFFER_SIZE];
        char receiveBuffer[BUFFER_SIZE];
        
        while (true) {
            printf("(if you wanna exit, type in any characters!) type in two integers: ");
            fflush(stdout);
            inputValid = scanf("%d %d", &integer1, &integer2);
            
            if (inputValid < 2) {
                printf("Inpur error\n");
                break;
            }
        
        memset(sendBuffer, 0, sizeof(BUFFER_SIZE));
        memset(receiveBuffer, 0, sizeof(BUFFER_SIZE));
            
        writtenBytes = sprintf(sendBuffer, "%d %d", integer1, integer2);
            //return a string
        writtenBytes = write(connectFD, sendBuffer, sizeof(sendBuffer));
        
        if (writtenBytes <= 0) {
            printf("Write error\n");
            break;
        }
            
        readBytes = read(connectFD,receiveBuffer,BUFFER_SIZE);
        if (readBytes <= 0) {
            printf("Read error\n");
            break;
        }
            
        printf("Result: %d + %d = %s\n", integer1, integer2, receiveBuffer);
        fflush(stdout);
        }
        close(connectFD);
        return 0;
    }
}
