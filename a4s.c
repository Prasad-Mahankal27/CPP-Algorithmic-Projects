#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0, readCount = 0;
pthread_mutex_t mutex;
sem_t wrt;

void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    std::cout << "Reader " << id << " reads data = " << data << std::endl;
    sleep(1);

    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&wrt);
    data++;
    std::cout << "Writer " << id << " writes data = " << data << std::endl;
    sleep(1);
    sem_post(&wrt);

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
        if (i < 2)
            pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < 5; i++) pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
