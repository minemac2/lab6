#include "queue.h"

//add items to queue
void enQueue(struct Queue* q,char* word,char* dir){
    struct node* temp=newNode(word,dir);

    if(q->rear == NULL){
        q->front=q->rear=temp;
        return;
    }

    q->rear->next=temp;
    q->rear=temp;


}

//remove items from queue
struct node* deQueue(struct Queue* q){

    if(q->front==NULL){
        return q->front;
    }

    struct node* temp=q->front;

    q->front=q->front->next;

    if(q->front==NULL)
        q->rear=NULL;

    return temp;

}

//print queue for debugging
void print(struct Queue* q)
{
    struct node* n = q->front;
    while (n != NULL) {
        printf(" %s  %s \n", n->word, n->dir);
        n = n->next;
    }
}


//returns size of queue
int getCount(struct Queue* q)
{
    int count = 0; 
    struct node* current = q->front; 
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

//Sorts the queue
void sort2(struct Queue* q)
{
    int i,j;
    char *a;
    char *b;

    struct node *h = q->front;

    struct node *temp1;
    struct node *temp2;

    for(temp1=h;temp1!=NULL;temp1=temp1->next)
      {
        for(temp2=temp1->next;temp2!=NULL;temp2=temp2->next)
          { 
            if(strcasecmp(temp2->word, temp1->word) < 0)
              {
                a = temp1->word;
                b = temp1->dir;

                temp1->word = temp2->word;
                temp1->dir = temp2->dir;
                temp2->word = a;
                temp2->dir = b;
              }
           }
       }
}

//creates and returns new node
struct node* newNode(char* word,char* dir){

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->word=word;
    temp->dir=dir;
    temp->next=NULL;
    return temp;

}

//returns new queue
struct Queue* createQueue(){
    struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
    q->front=q->rear=NULL;
    return q;
}