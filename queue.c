#include "queue.h"


void enQueue(struct Queue* q,char* word,char* dir){

    struct node* temp=newNode(word,dir);

    if(q->rear == NULL){
        q->front=q->rear=temp;
        return;
    }

    q->rear->next=temp;
    q->rear=temp;


}

void deQueue(struct Queue* q){

    if(q->front==NULL){
        return;
    }

    struct node* temp=q->front;

    q->front=q->front->next;

    if(q->front==NULL)
        q->rear=NULL;

    free(temp);

}