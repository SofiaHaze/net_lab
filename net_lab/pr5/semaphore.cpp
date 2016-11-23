//
//  semaphore.cpp
//
//
//  Created by 1 on 11/1/16.
//
//
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int sum = 0;
sem_t semaphore;
int limit = 1;


void* threadRoutine(void* argumentPointer) {
    sem_wait(&semaphore);
    for(int i = 0; i < 1000000; i++){
        sum ++;
    }
    sem_post(&semaphore);
}

int main() {
    
    pthread_t thread[2];
    sem_init(&semaphore, 0, limit);
    
    // threadRoutine을 실행하는 쓰레드 2개를 생성하시오.
    for(int i =0 ; i<2;i++){
        pthread_create(&thread[i], NULL, threadRoutine, NULL);
    }
    
    // 두 개의 thread를 join을 이용해 기다리시오.
    for(int i =0 ; i<2;i++){
        pthread_join(thread[i], NULL);
    }
    sem_destroy(&semaphore);
    printf("%d\n",sum);
    return 0;
}