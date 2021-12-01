#include "sortThread.h"



extern pthread_mutex_t writeMutex;
extern pthread_mutex_t sortMutex;


extern struct Queue *queue1;
extern struct Queue *queue2;

//main sort thread
void* sortThread(void* args)
{
    pthread_mutex_lock(&sortMutex);
    
    //sorting 10 words at a time
    struct Queue *queueToSort = createQueue();
    for(int i = 0; i < 10; i++)
    {
        if(getCount(queue1) > 0)
        {
            struct node* nodeToAdd = deQueue(queue1);
            enQueue(queueToSort, nodeToAdd->word, nodeToAdd->dir);
        }
    }
    sort2(queueToSort);
    pthread_mutex_unlock(&sortMutex);
    pthread_t tid[1];
    pthread_create(&tid[0], NULL, writeThread, (void*)queueToSort);
}

//second sort thread
void* writeThread(void* args)
{
    
    struct Queue* queueToSort = (struct Queue*)args;

    pthread_mutex_lock(&writeMutex);
    struct node* n = queueToSort->front;
    while (n != NULL) {
        enQueue(queue2, n->word, n->dir);
        n = n->next;
    }
    free(queueToSort);
    sort2(queue2);
    pthread_mutex_unlock(&writeMutex);
}