#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *((int *) arg);
    while (1) {
        int item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[count] = item;
        printf("Producer %d produced %d\n", id, item);
        count++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand() % 3);
    }
}

void* consumer(void* arg) {
    int id = *((int *) arg);
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        count--;
        int item = buffer[count];
        printf("Consumer %d consumed %d\n", id, item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand() % 3);
    }
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
