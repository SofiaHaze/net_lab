#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFER_SIZE 100

void* clnt_connection(void * arg);
void error_handling(char * message);


int clnt_number=0; //현재 접속자 수
int clnt_socks[10]; //최대 접속자 10명

pthread_mutex_t mutx;

int main(int argc, char **argv)
{
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int clnt_addr_size;
    pthread_t thread;
    
    if(argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    //무텍스 변수 초기화
    if(pthread_mutex_init(&mutx,NULL))
        error_handling("mutex init error");
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    //	FD_ZERO(&reads);
    //	FD_SET(serv_sock, &reads);
    //	fd_max = serv_sock;
    
    while(1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    
        //무텍스를 이용해서 컨커런트하게 연결된 소켓들을 관리
        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_number++]=clnt_sock;
        pthread_mutex_unlock(&mutx);
        
        pthread_create(&thread, NULL, clnt_connection, (void*) clnt_sock);
        printf(" IP : %s  Number of current connected users : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_number);
        
    }
    return 0;
    
}

void *clnt_connection(void *arg)
{
    //무텍스
    //pthread_mutex_lock(&mutx);
    
    int clnt_sock = (int) arg;
    int str_len=0;
    
    int integer1, integer2, sum;
    int readBytes, writtenBytes;4
    char sendBuffer[BUFFER_SIZE];
    char receiveBuffer[BUFFER_SIZE];
            
    while (1) {
                
        memset(sendBuffer, 0, sizeof(BUFFER_SIZE));
        memset(receiveBuffer, 0, sizeof(BUFFER_SIZE));
            
        readBytes = read(clnt_sock, receiveBuffer, BUFFER_SIZE);
                
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
        writtenBytes = write(clnt_sock, sendBuffer, sizeof(sendBuffer));
        if (writtenBytes <= 0) {
            printf("Write error");
            break;
        }
    }
    //pthread_mutex_unlock(&mutx);
    
    
    //연결이 끊어졌기 때문에 해당 클라이언트 소켓 닫아야함
    close(clnt_sock);
    
    //무텍스를 이용해서 컨커런트하게 연결된 소켓들을 관리
    pthread_mutex_lock(&mutx);
    
    int i=0;
    for(i=0;i<clnt_number;i++){
        if(clnt_sock == clnt_socks[i])
        {
            for(;i<clnt_number-1;i++)
                clnt_socks[i] = clnt_socks[i+1];
            break;
        }
    }
    clnt_number--;
    
    pthread_mutex_unlock(&mutx);
    
    close(clnt_sock);
    return 0;
}


void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}