#include "q.h"




void setupQueue1(int sizeMax){
    MAX=sizeMax;
    queueArray=(struct Words**)calloc(MAX,sizeof(struct Words**));
}

bool queueOneIsEmpty() {
    return itemCount == 0;
}

bool queueOneIsFull() {
    return itemCount == MAX;
}

int queueOneSize() {
    return itemCount;
}

int queueOneMax(){
    return MAX;
}

void printQueue(){
    for(int i=front;i<rear;i++){
        printf("%s  %s",queueArray[i]->word,queueArray[i]->pdir);
    }
    
}

//putting things in
void enqueue(char* data,char* qdir) {



    struct Words *p2={&data,qdir};
    printf("%s  %s\n",p2->word,p2->pdir);
    queueArray[rear] = p2;
    rear = (rear + 1) % MAX;
    itemCount++;
}

//taking stuff out
char* dequeue() {

    char* tmp = queueArray[front];
    front = (front + 1) % MAX;
    itemCount--;
    return tmp;
}
