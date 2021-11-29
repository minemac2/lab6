#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// extern void setupQueue1(int sizeMax);
// extern void closeQueue1();
// extern bool queueOneIsEmpty();
// extern bool queueOneIsFull();
// extern int queueOneSize();
// extern int queueOneMax();
// extern void printQueue();
// extern void enqueue(char* data,char* dir);
// extern void dequeue(char* word, char* dir);


int MAX;
char ** queueArrayWords;
char ** queueArrayDir;
int front = 0;
int rear = 0;
int itemCount = 0;


