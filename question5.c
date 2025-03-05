#define _XOPEN_SOURCE 600

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int grades[10];     
int total_grade = 0;
double total_bellcurve = 0;

pthread_mutex_t lock;
pthread_barrier_t barrier;

void *read_grades(void *arg) {
    FILE *file = fopen("grades.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        fscanf(file, "%d", &grades[i]);
    }
    fclose(file);

    pthread_barrier_wait(&barrier);
    return NULL;
}

void *save_bellcurve(void *arg) {
    int i = *(int *)arg;
    double bellcurve_grade = grades[i] * 1.50;

    pthread_mutex_lock(&lock);
    total_grade += grades[i];
    total_bellcurve += bellcurve_grade;

    FILE *file = fopen("bellcurve.txt", "a");
    if (file) {
        fprintf(file, "%.2f\n", bellcurve_grade);
        fclose(file);
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t read_thread, threads[10];
    int i, indices[10];

    pthread_mutex_init(&lock, NULL);
    pthread_barrier_init(&barrier, NULL, 2);

    pthread_create(&read_thread, NULL, read_grades, NULL);
    pthread_barrier_wait(&barrier);
    pthread_join(read_thread, NULL);

    FILE *file = fopen("bellcurve.txt", "w");
    if (file) fclose(file);

    for (i = 0; i < 10; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, save_bellcurve, &indices[i]);
    }

    for (i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total Grade: %d\n", total_grade);
    printf("Average Before: %.2f\n", total_grade / 10.0);
    printf("Total Bellcurved: %.2f\n", total_bellcurve);
    printf("Average After: %.2f\n", total_bellcurve / 10);

    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&barrier);

    return 0;
}

