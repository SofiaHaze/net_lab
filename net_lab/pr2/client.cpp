# include "header.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s IPv4-address\n", argv[0]);
        return -1;
    }
    struct sockaddr_in connectSocket;
    //클라이언트용 소켓(connectSocket)을 set 하시오
    connectSocket.sin_addr.s_addr = inet_addr(argv[1]);
    connectSocket.sin_family = AF_INET;
    connectSocket.sin_port = htons(PORT);
    
    int connectFD = socket(AF_INET, SOCK_STREAM, 0);
    
    if (connect(connectFD, (struct sockaddr*) &connectSocket, sizeof(connectSocket)) == -1) {
        printf("Can not connect.\n");
        return -1;
    } else {
        char buffer[BUFFER_SIZE];
        int n = (int)readvn(connectFD, buffer, (size_t)BUFFER_SIZE);
        printf("%d bytes read\n", n);
        buffer[n] = '\0';
        fputs(buffer, stdout);
        fflush(stdout);
    }
    close(connectFD);
    return 0;
}



ssize_t readLine(int socketFD,const char* buffer, size_t max){
    ssize_t readBytes,totalRead = 0;
    char* writingBuffer = buffer ;
    char c;
    
    for(totalRead =1 ; totalRead<max ; totalRead++){
        if(readBytes=read(socketFD,&c, 1))==1{
            
        }
    }

}

