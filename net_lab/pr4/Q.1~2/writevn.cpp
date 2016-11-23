# include "header.h"
# include <errno.h>
//errno를 위한 헤더를 추가하시오
ssize_t writen(int socketFD, char* buffer, size_t length) {
    size_t nleft = length;
    ssize_t nwritten;
    char* ptr = buffer;
    while(nleft>0){
        if ((nwritten = write (socketFD, ptr, nleft))<= 0) {
            if (errno == EINTR)
                nwritten = 0; // call write again
            else return (-1);
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (length); // return >= 0
}
ssize_t writevn(int socketFD, char* buffer, size_t length) {
    int size = length;
    writen(socketFD, (char*)&size, sizeof(size));
    writen(socketFD, buffer, length);
    return (length); // return >= 0
}
