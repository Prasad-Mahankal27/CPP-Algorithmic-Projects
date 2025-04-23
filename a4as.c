#include <iostream>
#include <pthread.h>
#include <unistd.h>

int data = 0;

void* reader(void* arg) {
    int id = *(int*)arg;
    std::cout << "Reader " << id << " reads data = " << data << std::endl;
    sleep(1);  // Simulate reading time
    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *(int*)arg;
    data++;  // Write operation (increments shared data)
    std::cout << "Writer " << id << " writes data = " << data << std::endl;
    sleep(1);  // Simulate writing time
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5];

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;

        if (pthread_create(&readers[i], NULL, reader, &ids[i]) != 0)
            perror("Reader thread creation failed");

        if (i < 2) {
            if (pthread_create(&writers[i], NULL, writer, &ids[i]) != 0)
                perror("Writer thread creation failed");
        }
    }

    for (int i = 0; i < 5; i++) pthread_join(readers[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(writers[i], NULL);

    return 0;
}
