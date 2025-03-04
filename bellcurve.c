#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_STUDENTS 5

void* bellcurve(void* arg) {
    int grade = *(int*)arg; // convert void* to int*
    float bellcurved_grade = grade * 1.50; //multiply by 1.5 for the bellcurve
    printf("Original Grade: %d, Bellcurved Grade: %.2f\n", grade, bellcurved_grade);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_STUDENTS]; // thread array to store all the values
    int grades[NUM_STUDENTS];

    // prompt user for the grades
    printf("Enter %d student grades: ", NUM_STUDENTS);
    for (int i = 0; i < NUM_STUDENTS; i++) {
        scanf("%d", &grades[i]);
    }

    // create threads for all the students grades
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_create(&threads[i], NULL, bellcurve, &grades[i]);
    }

    // waiting for all threads to complete execution
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
