#include <stdio.h>

#include "list.h"

void initList(List *list, size_t initSize)
{
    if (list == NULL)
    {
        printf("could not access List*");
        exit(EXIT_FAILURE);
    }
    if (initSize < 1)
    {
        printf("given size to allocate was < 1");
        exit(EXIT_FAILURE);
    }

    list->arrayPtr = (int*)malloc(initSize * sizeof(int));

    if (list->arrayPtr == NULL)
    {
        printf("failed to allocate space for list->arrayPtr");
        exit(EXIT_FAILURE);
    }

    list->size = initSize;
    list->length = 0;
}

void addToList(List *list, int element)
{
    if (list == NULL)
    {
        printf("could not access List*");
        exit(EXIT_FAILURE);
    }
    if (list->size == list->length)
    {
        expandList(list, 2);
    }

    list->arrayPtr[list->length] = element;
    list->length++;
}

void expandList(List *list, int factor)
{
    printf("trying to expand list by %d\n", factor);

    if (list == NULL)
    {
        printf("could not access List*");
        exit(EXIT_FAILURE);
    }

    int *ptr = (int*)malloc(list->size * factor * sizeof(int));
    if (ptr == NULL)
    {
        printf("failed to allocate new space to expand list");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < list->length; i++)
    {
        ptr[i] = list->arrayPtr[i];
    }

    free(list->arrayPtr);
    list->arrayPtr = ptr;
    list->size *= factor;
}

void freeList(List *list)
{
    if (list == NULL)
    {
        printf("could not access List*");
        exit(EXIT_FAILURE);
    }
    if (list->arrayPtr == NULL)
    {
        printf("could not free arrayPtr - it was NULL");
        exit(EXIT_FAILURE);
    }

    free(list->arrayPtr);
    list->arrayPtr = NULL;
}

void printList(List *list)
{
    if (list == NULL)
    {
        printf("could not access List*");
        exit(EXIT_FAILURE);
    }
    if (list->arrayPtr == NULL)
    {
        printf("could read arrayPtr - it was NULL");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < list->length; i++)
    {
        printf("list[%d] = %d\n", i, list->arrayPtr[i]);
    }
}