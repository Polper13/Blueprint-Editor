#pragma once

#include <stdlib.h>

typedef struct 
{
    int *arrayPtr;
    int length;
    int size;
}List;

void initList(List *list, size_t initSize);
void addToList(List *list, int element);
void expandList(List *list, int factor);
void freeList(List *list);

void printList(List *list);