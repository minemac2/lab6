#include "q1.h"




void queueOneSetup(int sizeMax){
    QUEUEONEMAX=sizeMax;
    queueOneArrayWords=(char**)calloc(QUEUEONEMAX,sizeof(char**));
    queueOneArrayDir=(char**)calloc(QUEUEONEMAX,sizeof(char**));
}

void queueOneClose(){
    free(queueOneArrayWords);
    free(queueOneArrayDir);
}

bool queueOneIsEmpty() {
    return queueOneItemCount == 0;
}

bool queueOneIsFull() {
    return queueOneItemCount == QUEUEONEMAX;
}

int queueOneSize() {
    return queueOneItemCount;
}

int queueOneMax(){
    return QUEUEONEMAX;
}

void queueOnePrint(){
    for(int i=queueOneFront;i<queueOneRear;i++){
        printf("%s  %s\n",queueOneArrayWords[i],queueOneArrayDir[i]);
    }
    
}

//putting things in
void queueOneEnqueue(char* data,char* dir) {

    queueOneArrayWords[queueOneRear] = data;
    queueOneArrayDir[queueOneRear] = dir;
    //printf("Word: %s Dir: %s\n",queueArrayWords[rear],queueArrayDir[rear]);
    queueOneRear = (queueOneRear + 1) % QUEUEONEMAX;
    queueOneItemCount++;
}

//taking stuff out
void queueOneDequeue(char* word, char* dir) {

    word=(char*)malloc(sizeof(queueOneArrayWords[queueOneFront]));
    *word = *queueOneArrayWords[queueOneFront];
    free(queueOneArrayWords[queueOneFront]);

    dir=(char*)malloc(sizeof(queueOneArrayDir[queueOneFront]));
    *dir = *queueOneArrayDir[queueOneFront];
    free(queueOneArrayDir[queueOneFront]);

    queueOneFront = (queueOneFront + 1) % QUEUEONEMAX;
    queueOneItemCount--;
    return;
}
