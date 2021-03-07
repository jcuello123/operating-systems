#include <stdio.h>
#include <semaphore.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t question_lock;
sem_t capacity;
/*
validate_parameter:
=======================
Description: This function ensures that our command line arguments are valid inputs,
they must valid integers and nothing else.
*/
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
/*
Professor | Student print actions:
==================================
These functions are in charge of printing the current status of our students and
their questions.
*/
void leave_office(int student){
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
    printf("Student %d asks a question.\n", student);
}

void enter_office(int student){
    printf("Student %d enters the office.\n", student);
}
/*
Start:
==========
This function is in charge of being called when a thread first starts.
Each thread runs this function to keep track of entering the room and asking questions,
then finally leaves the room to let another 'student' in.
*/
void *start(void *arg){
    int student = (intptr_t) arg;
//calculate the amount of questions per student
    int questions = (student % 4) + 1;

    sem_wait(&capacity);
    enter_office(student);
//While the student still has questions then ask until they have no more.
    while(questions > 0){
        pthread_mutex_lock(&question_lock);
        question_start(student);
        answer_start(student);
        answer_done(student);
        question_done(student);
        pthread_mutex_unlock(&question_lock);
        questions--;
    }

    leave_office(student);
    sem_post(&capacity);
}

int main(int argc, char* argv[]){   
    validate_parameter(argv[1]);
    validate_parameter(argv[2]);
//convert args to integers
    int number_of_threads = atoi(argv[1]);
    int max_capacity = atoi(argv[2]);
//initialize mutex and semaphore
    pthread_mutex_init(&question_lock, NULL);
    sem_init(&capacity, 0, max_capacity);

    pthread_t tid;
    //create number of threads 'students'
    for (int i = 0; i < number_of_threads; i++){
        pthread_create(&tid, NULL, start, (void *)(intptr_t) i);
    }

		
    pthread_join(tid, NULL);
	printf("The Professor has finished answering everyone's questions!\n"); 
	pthread_exit(NULL);	
    return 0;
}
