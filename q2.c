#include "q2.h"




void queueTwoSetup(int sizeMax){
    QUEUETWOMAX=sizeMax;
    queueTwoArrayWords=(char**)calloc(QUEUETWOMAX,sizeof(char**));
    queueTwoArrayDir=(char**)calloc(QUEUETWOMAX,sizeof(char**));
}

void queueTwoClose(){
    free(queueTwoArrayWords);
    free(queueTwoArrayDir);
}

bool queueTwoIsEmpty() {
    return queueTwoItemCount == 0;
}

bool queueTwoIsFull() {
    return queueTwoItemCount == QUEUETWOMAX;
}

int queueTwoSize() {
    return queueTwoItemCount;
}

int queueTwoMax(){
    return QUEUETWOMAX;
}

void queueTwoPrint(){
    for(int i=queueTwoFront;i<queueTwoRear;i++){
        printf("%s  %s\n",queueTwoArrayWords[i],queueTwoArrayDir[i]);
    }
    
}

//putting things in
void queueTwoEnqueue(char* data,char* dir) {

    queueTwoArrayWords[queueTwoRear] = data;
    queueTwoArrayDir[queueTwoRear] = dir;
    //printf("Word: %s Dir: %s\n",queueArrayWords[rear],queueArrayDir[rear]);
    queueTwoRear = (queueTwoRear + 1) % QUEUETWOMAX;
    queueTwoItemCount++;
}

//taking stuff out
void queueTwoDequeue(char* word, char* dir) {

    word=(char*)malloc(sizeof(queueTwoArrayWords[queueTwoFront]));
    *word = *queueTwoArrayWords[queueTwoFront];
    free(queueTwoArrayWords[queueTwoFront]);

    dir=(char*)malloc(sizeof(queueTwoArrayDir[queueTwoFront]));
    *dir = *queueTwoArrayDir[queueTwoFront];
    free(queueTwoArrayDir[queueTwoFront]);

    queueTwoFront = (queueTwoFront + 1) % QUEUETWOMAX;
    queueTwoItemCount--;
    return;
}
