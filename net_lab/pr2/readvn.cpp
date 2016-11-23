# include "header.h"
# include <errno.h>
//errno를 위한 헤더를 추가하시오

ssize_t readn(int socketFD, char* buffer, size_t length) {
    size_t nleft = length;		// 받으려는 문자열의 길이
    ssize_t nread;			// 읽은 문자의 수
    char *ptr = buffer;
    while(nleft>0){			// 받으려는 문자가 남은 경우
        if((nread=read(socketFD,ptr,nleft))<0){
            if(errno == EINTR){ nread = 0; }	//INTR
            else{ return -1; }			// 연결 강제 해제
        } else if (nread == 0){ break; }	//EOF
        nleft -= nread;		// 한 번에 못 읽을 경우
        ptr += nread;			// 다음 읽을 수를 지정
    }
    return (length-nleft);
}

ssize_t readvn(int socketFD, char* buffer, size_t maxLength) {
    int reclen;		// 헤더에 저장된 문자열의 길이
    int rc;		// 읽은 문자열의 길이
    // 헤더를 읽어 정수형의 메세지 길이를 받았는지 확인
    rc = (int)readn(socketFD, (char *)&reclen, sizeof(int));
    if(rc != sizeof(int)) return rc<0 ? -1 : 0;
    if(reclen> maxLength){	// 최대길이보다 받은 문자열이 긴 경우
        while (reclen > 0) // 버려줍니다.
        {
            rc = (int)readn(socketFD, buffer, maxLength);
            if (rc != maxLength) return rc < 0 ? -1 : 0;
            reclen -= maxLength;
            if (reclen < maxLength) maxLength = reclen;
        }
        errno=EMSGSIZE;	// 메세지 사이즈 에러
        return -1;
    }
    rc = (int)readn(socketFD, buffer, reclen);
    if( rc != reclen ){	// 메세지가 기대한 만큼 읽어지지 않은 경우
        return rc<0 ? -1 : 0;
    }
    return rc;
}
