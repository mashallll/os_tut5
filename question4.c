#include <stdio.h>
#include <pthread.h>

int total_grade = 0;
pthread_mutex_t lock;

void *class_total(void *arg) {
    int grade = *(int *)arg;

    pthread_mutex_lock(&lock);
    total_grade += grade;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t threads[10];
    int grades[10];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 10; i++) {
        printf("Enter grade for student %d: ", i + 1);
        scanf("%d", &grades[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, class_total, &grades[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total class grade: %d\n", total_grade);

    pthread_mutex_destroy(&lock);

    return 0;
}
