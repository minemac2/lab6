#include "q.h"

int peek() {
    return intArray[front];
}

bool isEmpty() {
    return itemCount == 0;
}

bool isFull() {
    return itemCount == MAX;
}

int size() {
    return itemCount;
}

void insert(int data) {

    if(!isFull()) {

        if(rear == MAX-1) {
            rear = -1;
        }

        intArray[++rear] = data;
        itemCount++;
    }
}

int removeData() {
    int data = intArray[front++];

    if(front == MAX) {
        front = 0;
    }

    itemCount--;
    return data;
}
