#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>




struct node{
    char * word;
    char * dir;
    struct node *next;
};
typedef struct node node;

struct Queue {
    //struct node;
    int count;
    node *front;
    node *rear;

};
typedef struct Queue Queue;

struct node* newNode(char* word,char* dir){

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->word=word;
    temp->dir=dir;
    temp->next=NULL;
    return temp;

}

struct Queue* createQueue(){
    struct Queue* q=(struct Queue*)malloc(sizeof(struct Queue));
    q->front=q->rear=NULL;
    return q;
}


