#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

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
    char *data_type;
} LinkedList;

// """costruttore"""
LinkedList *newLinkedList(char *data_type);

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
int size(LinkedList *);
size_t size_of(char *);
char *tolower_str(const char*);

#define InsertAt(this, data, index) \
    insert_at(this, &data, index, sizeof(data))

#define AddFirst(this, data) \
    add_first(this, &data, sizeof(data))

#define Add(this, data) \
    add(this, &data, sizeof(data))

#define Clear(this) \
    clear(this)

#define RemoveLast(this) \
    remove_last(this)

#define RemoveHead(this) \
    remove_head(this)

#define RemoveAt(this, index) \
    remove_at(this, index)

#define ReplaceHead(this, data, index) \
    replace_head(this, &data, sizeof(data))

#define ReplaceAt(this, data, index) \
    replace_at(this, &data, index, sizeof(data))

#define GetHead(this) ( \
    ((this) == NULL || (this)->head == NULL) ? NULL : (*(typeof((this)->head->data))((this)->head->data)))

// non creo la funzione get_head(...) perché avendo un tipo generico per i valori della lista
// dovrei ritornare un puntatore void (castato poi al tipo di data_type della lista)
// quindi voglio evitare che un poi io mi debba gestire i puntatori dal main
// così facendo invece vado a prendere direttamente il valore contenuto
#define GetLast(this) ( \
    ((this) == NULL || (this)->last == NULL) ? NULL : (*(typeof((this)->last->data))((this)->last->data)))

// anche qua scrivo un if ternario e ciclo tutta la lista finche non trovo
#define Get(this, index) (                                                   \
    ((this) == NULL || (index) < 0) ? NULL : ({                              \
        typeof((this)->head) node = (this)->head;                            \
        int i = 0;                                                           \
        while (node->next != NULL && i < (index))                            \
        {                                                                    \
            node = node->next;                                               \
            i++;                                                             \
        }                                                                    \
        (node == NULL) ? NULL : (*(typeof((this)->head->data))(node->data)); \
    }))

#define PrintList(this) \
    print_list(this)

#define Size(this) \
    size(this)

#define TypeOf(T) _Generic((T),               \
    char: "char",                             \
    signed char: "signed char",               \
    unsigned char: "unsigned char",           \
    short: "short",                           \
    unsigned short: "unsigned short",         \
    int: "int",                               \
    unsigned int: "unsigned int",             \
    long: "long",                             \
    unsigned long: "unsigned long",           \
    long long: "long long",                   \
    unsigned long long: "unsigned long long", \
    float: "float",                           \
    double: "double",                         \
    long double: "long double",               \
    char *: "string",                         \
    LinkedList: "LinkedList",                 \
    LinkedList *: "LinkedList *",             \
    Node: "Node",                             \
    Node *: "Node *",                         \
    default: "unknown")

#define SizeOf(T) \
    size_of(T)

#define ToLower(s)\
    tolower_str(s)

#endif
