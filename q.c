#include "q.h"




void setupQueue1(int sizeMax){
    MAX=sizeMax;
    queueArrayWords=(char**)calloc(MAX,sizeof(char**));
    queueArrayDir=(char**)calloc(MAX,sizeof(char**));
}

void closeQueue1(){
    free(queueArrayWords);
    free(queueArrayDir);
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
        printf("%s  %s\n",queueArrayWords[i],queueArrayDir[i]);
    }
    
}

//putting things in
void enqueue(char* data,char* dir) {

    queueArrayWords[rear] = data;
    queueArrayDir[rear] = dir;
    //printf("Word: %s Dir: %s\n",queueArrayWords[rear],queueArrayDir[rear]);
    rear = (rear + 1) % MAX;
    itemCount++;
}

//taking stuff out
void dequeue(char* word, char* dir) {

    word=(char*)malloc(sizeof(queueArrayWords[front]));
    *word = *queueArrayWords[front];
    free(queueArrayWords[front]);

    dir=(char*)malloc(sizeof(queueArrayDir[front]));
    *dir = *queueArrayDir[front];
    free(queueArrayDir[front]);

    front = (front + 1) % MAX;
    itemCount--;
    return;
}
