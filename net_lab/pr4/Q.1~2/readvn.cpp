# include "header.h"
# include <errno.h>
//errno를 위한 헤더를 추가하시오

ssize_t readn(int socketFD, char* buffer, size_t length) {
    size_t nleft = length;
    ssize_t nread;
    char *ptr = buffer;
    while(nleft>0){
        if((nread=read(socketFD,ptr,nleft))<0){
            if(errno == EINTR){ nread = 0; }
            else{ return -1; }
        } else if (nread == 0){ break; }
        nleft -= nread;
        ptr += nread;
    }
    return (length-nleft);
}
ssize_t readvn(int socketFD, char* buffer, size_t maxLength) {
    int reclen;
    int rc;
    
    rc = (int)readn(socketFD, (char *)&reclen, sizeof(int));
    if(rc != sizeof(int)) return rc<0 ? -1 : 0;
    if(reclen> maxLength){
        while (reclen > 0)
        {
            rc = (int)readn(socketFD, buffer, maxLength);
            if (rc != maxLength) return rc < 0 ? -1 : 0;
            reclen -= maxLength;
            if (reclen < maxLength) maxLength = reclen;
        }
        errno=EMSGSIZE;
        return -1;
    }
    rc = (int)readn(socketFD, buffer, reclen);
    if( rc != reclen ){
        return rc<0 ? -1 : 0;
    }
    return rc;
}
