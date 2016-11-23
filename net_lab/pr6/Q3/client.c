#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFER_SIZE 100
#define NAMESIZE 20
void *send_message( void *arg );
void *communication( void *arg );

void *recv_message( void *arg );
void error_handling( char* message );
char name[NAMESIZE] = "[Default]";
char message[BUFFER_SIZE];

int main( int argc , char** argv )
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_result;
    
    if( argc != 3 )
    {
        printf( "Usage : %s <IP> <port>\n " , argv[0] );
        exit( 1 );
    }
    sock = socket( PF_INET , SOCK_STREAM , 0 );
    if( sock == 1 )
        error_handling( "socket() error" );
    
    memset( &serv_addr , 0 , sizeof( serv_addr ) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr( argv[1] );
    serv_addr.sin_port = htons( atoi( argv[2] ) );

    if( connect( sock , (struct sockaddr*) &serv_addr , sizeof( serv_addr ) ) == -1 )
        error_handling( "bind() error" );
    
    //쓰레드 미리 생성!
    pthread_create( &snd_thread , NULL , communication , ( void* ) sock );
    pthread_join( snd_thread , &thread_result );
    
    close( sock );
    return 0;
}



void *communication(void *arg){
    int connectFD = (int)arg;
    
    int integer1, integer2, inputValid;
    int readBytes, writtenBytes;
    char sendBuffer[BUFFER_SIZE];
    char receiveBuffer[BUFFER_SIZE];
    
    while (1) {
        printf("(if you wanna exit, type in any characters!) type in two integers: ");
        inputValid = scanf("%d %d", &integer1, &integer2);
        
        if (inputValid < 2) {
            printf("Inpur error\n");
            fflush(stdout);
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

}


void error_handling( char *message )
{
    fputs( message , stderr );
    fputs( '\n' , stderr );
    exit( 1 );
}