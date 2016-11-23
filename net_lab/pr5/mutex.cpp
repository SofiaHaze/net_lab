//
//  mutex.cpp
//  
//
//  Created by 1 on 11/1/16.
//
//
#include <stdio.h>
#include <pthread.h>

int sum = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadRoutine(void* argumentPointer) {
    pthread_mutex_lock(&counter_mutex);
    for(int i = 0; i < 1000000; i++){
        sum ++;
    }
    pthread_mutex_unlock(&counter_mutex);
}

int main() {
    
    pthread_t thread[2];
    // threadRoutine을 실행하는 쓰레드 2개를 생성하시오.
    for(int i =0 ; i<2;i++){
        pthread_create(&thread[i], NULL, threadRoutine, NULL);
    }
    
    // 두 개의 thread를 join을 이용해 기다리시오.
    for(int i =0 ; i<2;i++){
        pthread_join(thread[i], NULL);
    }
    pthread_mutex_destroy(&counter_mutex);
    printf("%d\n",sum);
    
    return 0;
}