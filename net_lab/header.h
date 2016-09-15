//
//  header.h
//  net_lab
//
//  Created by 1 on 9/14/16.
//  Copyright (c) 2016 1. All rights reserved.
//


# include <stdio.h> 
# include <string.h>
/********/
//TCP 소캣 프로그램을 위한 헤더 파일을 include 하시오 /********/

# include <netinet/in.h>
# include <sys/socket.h> 
# include <arpa/inet.h> 
# include <unistd.h>
# define PORT 10000
# define BUFFER_SIZE 100