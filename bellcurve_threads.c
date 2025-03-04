#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 5

typedef struct {
    char name[50];
    int student_id;
    float grade;
} student;

void* bellcurve(void* arg) {
    student* s = (student*)arg;
    float bellcurved_grade = s->grade * 1.5;

    printf("Student Name: %s\n", s->name);
    printf("Student ID: %d\n", s->student_id);
    printf("Bellcurved Grade: %.2f\n\n", bellcurved_grade);

    return NULL;
}

int main() {}
    student students[NUM_STUDENTS];
    pthread_t threads[NUM_STUDENTS];

    // Prompt the professor for student data
    for (int i = 0; i < NUM_STUDENTS; i++) {
        printf("Enter name for student %d: ", i + 1);
        scanf("%s", students[i].name);

        printf("Enter student ID for student %d: ", i + 1);
        scanf("%d", &students[i].student_id);

        printf("Enter grade for student %d: ", i + 1);
        scanf("%f", &students[i].grade);

        printf("\n");
    }

    // Create one thread per student to process the bellcurve
    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&threads[i], NULL, bellcurve, (void*)&students[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
