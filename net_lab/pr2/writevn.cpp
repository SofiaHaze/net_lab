# include "header.h"
# include <errno.h>
//errno를 위한 헤더를 추가하시오
ssize_t writen(int socketFD, char* buffer, size_t length) {
    size_t nleft = length;	// 입력한 문자열의 길이
    ssize_t nwritten;		// 한 번의 write로 전송한 문자 수
    char* ptr = buffer;
    
    while(nleft>0){		// 전송할 문자가 남아있다면
        if ((nwritten = write (socketFD, ptr, nleft))<= 0) {
            if (errno == EINTR)	// 인터럽트가 걸린 경우
                nwritten = 0; 	// call write again
            else return (-1);	// 상대방이 강제로 연결을 끊은 경우
        }
        nleft -= nwritten;		// 한 번의 write로 모두 못 보낼 수
        ptr += nwritten;		// 있으므로 다음 write를 준비합니다.
    }
    return (length); 			// return >= 0
}
ssize_t writevn(int socketFD, char* buffer, size_t length) {
    int size = length;
    writen(socketFD, (char*)&size, sizeof(size));// header 부분
    writen(socketFD, buffer, length);			// variable 부분
    return (length); 						// return >= 0
}
