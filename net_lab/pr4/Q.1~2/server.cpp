#include "header.h"

#define LISTEN_QUEUE_SIZE 5

void childHandler(int sig){
    //모든 child process가 종료될 때까지 기다리시오.
	while(waitpid(-1,0,WNOHANG)>0); //임의의 자식 프로세스가 종료되기를 기다림 -1은 wait와 같음
	return;
}

void echo(int fd){
	int recvSize;
	char buffer[BUFFER_SIZE]={0};
	recvSize = (int)readvn(fd, buffer, sizeof(buffer));
	buffer[recvSize] ='\0';
	printf("%s\n",buffer);
	writevn(fd, buffer, sizeof(buffer));
}

int main(){
	
    //childHandler 함수가 SIGCHLD 시그널을 처리할 수 있도록 하시오.
	signal(SIGCHLD, childHandler);
	
    struct sockaddr_in listenSocket;
	memset(&listenSocket, 0 , sizeof(listenSocket));
	listenSocket.sin_family = AF_INET;
	listenSocket.sin_addr.s_addr = htonl(INADDR_ANY );
	listenSocket.sin_port = htons(PORT);
	int listenFD = socket(AF_INET, SOCK_STREAM, 0);
	
	if (bind(listenFD, (struct sockaddr *) &listenSocket, sizeof(listenSocket)) == -1) {
		printf("Can not bind.\n");
		return -1;
	}
	if (listen(listenFD, LISTEN_QUEUE_SIZE) == -1) {
		printf("Listen fail.\n");
		return -1;
	}
	printf("Waiting for clients...\n");
	while (1) {
		struct sockaddr_in connectSocket, peerSocket;
		socklen_t connectSocketLength = sizeof(connectSocket);
		int connectFD = accept(listenFD, (struct sockaddr*)&connectSocket, &connectSocketLength);
		
        getpeername(connectFD, (struct sockaddr*)&peerSocket, &connectSocketLength);
		char peerName[sizeof(peerSocket.sin_addr) + 1] = {0};
		sprintf(peerName, "%s", inet_ntoa(peerSocket.sin_addr));
		printf("Client : %s\n", peerName);
        
        //클라이언트가 접속할 때마다 fork를 통해 child process를 생성해 echo를 수행하시오.
		if(fork()==0){
			close(listenFD);
			echo(connectFD);
			close(connectFD);
			exit(0);		
		}
		close(connectFD);
	}
	close(listenFD);
	return 0;
}
