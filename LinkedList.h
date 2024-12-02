#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef enum
{
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING
} DataType;

typedef struct Node
{
    struct Node *prev;
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    struct Node *head;
    struct Node *last;
    size_t size;
    size_t data_size; // Dimensione di ogni elemento
    DataType data_type;
} LinkedList;

LinkedList *newLinkedList(DataType data_type);

bool insert_at(LinkedList *, void *, int, size_t);
bool add_first(LinkedList *, void *, size_t);
bool add(LinkedList *, void *, size_t);
bool clear(LinkedList *);
bool remove_last(LinkedList *);
bool remove_head(LinkedList *);
bool remove_at(LinkedList *, int);
bool replace_head(LinkedList *, void *, size_t);
bool replace_at(LinkedList *, void *, int, size_t);
void print_list(LinkedList *);
void get(LinkedList *, int);
int size_of(LinkedList *);

#define InsertAt(list, data, index) \
    insert_at(list, &data, index, sizeof(data))

#define AddFirst(list, data) \
    add_first(list, &data, sizeof(data))

#define Add(list, data) \
    add(list, &data, sizeof(data))

#define Clear(list) \
    clear(list)

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

#define GetHead(list) ( \
    ((list) == NULL || (list)->head == NULL) ? NULL : (*(typeof((list)->head->data))((list)->head->data)))

// non creo la funzione get_head(...) perché avendo un tipo generico per i valori della lista
// dovrei ritornare un puntatore void (castato poi al tipo di data_type della lista)
// quindi voglio evitare che un poi io mi debba gestire i puntatori dal main
// così facendo invece vado a prendere direttamente il valore contenuto
#define GetLast(list) ( \
    ((list) == NULL || (list)->last == NULL) ? NULL : (*(typeof((list)->last->data))((list)->last->data)))

#define Get(list, index) \
        get(list, index)

#define PrintList(list) \
        print_list(list)

#define SizeOf(list) \
        size_of(list)

#endif