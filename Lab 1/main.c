#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

int shared_variable = 0;
pthread_mutex_t lock;
pthread_barrier_t barrier;

void validate_parameter(char number[]){
    if (number == NULL){
        printf("Parameter isn't a valid number. Exiting the program..\n");
        exit(-1);
    }

    for (int i = 0; number[i] != '\0'; i++){
        if (!isdigit(number[i])){
            printf("Parameter isn't a valid number. Exiting the program..\n");
            exit(-1);
        }
    }
}

void *modify_variable(void *arg){
    int current_thread = (intptr_t) arg;

    for (int i = 0; i < 20; i++){
    #ifdef PTHREAD_SYNC
        pthread_mutex_lock(&lock);
    #endif

        printf("thread %d sees value %d\n", current_thread, shared_variable);
        shared_variable++;

    #ifdef PTHREAD_SYNC
        pthread_mutex_unlock(&lock);
    #endif
    }
    
    #ifdef PTHREAD_SYNC
        pthread_barrier_wait(&barrier);
    #endif

    printf("*** thread %d sees final value %d  ***.\n", current_thread, shared_variable);
}

int main(int argc, char* argv[]){
    
    validate_parameter(argv[1]);
    int number_of_threads = atoi(argv[1]);

    #ifdef PTHREAD_SYNC
        pthread_mutex_init(&lock, NULL);
        pthread_barrier_init(&barrier, NULL, number_of_threads);
    #endif

    pthread_t tid;
    
    for (int i = 0; i < number_of_threads; i++){
        pthread_create(&tid, NULL, modify_variable, (void *)(intptr_t) i);
    }

    pthread_join(tid, NULL);
    pthread_exit(NULL);
    return 0;
}

