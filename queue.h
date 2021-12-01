#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node{
    char * word;
    char * dir;
    struct node *next;
} node;

struct Queue {
    int count;
    node *front;
    node *rear;

};
typedef struct Queue Queue;



extern void enQueue(struct Queue* q,char* word,char* dir);
extern struct node* deQueue(struct Queue* q);
extern void print(struct Queue* q);
extern int getCount(struct Queue* q);
extern struct Queue* createQueue();
extern struct node* newNode(char* word,char* dir);
extern void sort2(struct Queue* q);


