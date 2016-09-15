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
        char buffer[BUFFER_SIZE];
        long n = read(connectFD, buffer, BUFFER_SIZE);
        printf("%ld bytes read\n", n);
        buffer[n] = '\0';
        fputs(buffer, stdout);
        fflush(stdout);
    } close(connectFD);
    return 0;
    
}