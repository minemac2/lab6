#include <semaphore.h>

extern void* readFromFile(char* filename, struct Queue *q,sem_t *mutex,sem_t *empty,sem_t *full);