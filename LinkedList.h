#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef enum { INT, FLOAT, DOUBLE, CHAR, STRING } DataType;

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    size_t data_size; // Dimensione di ogni elemento
    DataType data_type;
} LinkedList;

LinkedList *newLinkedList(DataType data_type);

bool add_at_index(LinkedList*,void*,int,size_t);
bool add_in_front(LinkedList*,void*,size_t);
bool add(LinkedList*,void*,size_t);
bool free_list(LinkedList*);
bool remove_last(LinkedList*);
bool remove_head(LinkedList*);
bool remove_at(LinkedList*, int);
bool replace_head(LinkedList*, void*,size_t);
bool replace_at(LinkedList*, void*,int,size_t);
void print_list(LinkedList*);
int size_of(LinkedList*);

#define AddAtIndex(list, data, index) \
    add_at_index(list, &data, index, sizeof(data))
#define AddInFront(list, data) \
    add_in_front(list, &data, sizeof(data))
#define Add(list, data) \
    add(list, &data, sizeof(data))
#define FreeList(list) \
    free_list(list)
#define RemoveLast(list) \
    remove_last(list)
#define RemoveHead(list) \
    remove_head(list)
#define RemoveAt(list, index) \
    remove_at(list, index)
#define ReplaceHead(list, data, index) \
    replace_head(list, &data, sizeof(data))
#define ReplaceAt(list, data, index) \
    replace_at(list, &data, index, sizeof(data))
#define PrintList(list) \
    print_list(list)
#define SizeOf(list) \
    size_of(list)

#endif