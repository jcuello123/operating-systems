#include <stdio.h>
#include <semaphore.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

int max_capacity;
int current_capacity = 0;
pthread_mutex_t question_lock;
sem_t room_lock;
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

void leave_office(int student){
    current_capacity--;
    printf("Student %d leaves the office.\n", student);
}

void question_done(int student){
    printf("Student %d is satisfied.\n", student);
}

void answer_done(int student){
    printf("Professor is done with answer for student %d\n", student);
}

void answer_start(int student){
    printf("Professor starts to answer question for student %d\n", student);
}

void question_start(int student){
    pthread_mutex_lock(&question_lock);
    printf("Student %d asks a question.\n", student);
    answer_start(student);
    answer_done(student);
    question_done(student);
    pthread_mutex_unlock(&question_lock);
}

void enter_office(int student){
    current_capacity++;
    printf("Student %d enters the office.\n", student);
}

void *start(void *arg){
    int student = (intptr_t) arg;
    int questions = (student % 4) + 1;

    sem_wait(&room_lock);
    enter_office(student);

    while(questions > 0){
        question_start(student);
        questions--;
    }

    leave_office(student);
    sem_post(&room_lock);

    //pthread_mutex_lock(&lock);

    //pthread_mutex_unlock(&lock);
    
    //pthread_barrier_wait(&barrier);
}

int main(int argc, char* argv[]){   
    validate_parameter(argv[1]);
    validate_parameter(argv[2]);
    int number_of_threads = atoi(argv[1]);
    max_capacity = atoi(argv[2]);
    
    pthread_mutex_init(&question_lock, NULL);
    sem_init(&room_lock, 0, max_capacity);
    //pthread_barrier_init(&barrier, NULL, number_of_threads);

    pthread_t tid;
    
    for (int i = 0; i < number_of_threads; i++){
        pthread_create(&tid, NULL, start, (void *)(intptr_t) i);
    }

    pthread_join(tid, NULL);
    pthread_exit(NULL);
    return 0;
}

