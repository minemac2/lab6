#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Words {
    char* word; 
    char* pdir;
};

int MAX;
struct Words** queueArray;
int front = 0;
int rear = 0;
int itemCount = 0;


