#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define newLinkedList(type) \
    CreateList(sizeof(type), #type)

#define InsertAt(list, data, index)                              \
    {                                                            \
        __typeof__(data) _tmp = (data);                          \
        insert_at(list, &_tmp, index, sizeof(__typeof__(_tmp))); \
    }

#define AddFirst(list, data)                              \
    {                                                     \
        __typeof__(data) _tmp = (data);                   \
        add_first(list, &_tmp, sizeof(__typeof__(_tmp))); \
    }

#define Add(list, data)                                                                                                                                   \
    {                                                                                                                                                     \
        __typeof__(data) *_tmp = (data);                                                                                                                  \
        add(list, &_tmp, ((list == NULL) ? 0 : ((GetHead(list) == NULL) ? (SetHead(list, &_tmp, __typeof__(_tmp)), 1) : SameType(GetHead(list), _tmp)))); \
    }

#define SetHead(list, data, type) \
    set_head(list, data, #type)

#define Clear(list) \
    clear(list)

#define RemoveLast(list) \
    remove_last(list)

#define RemoveHead(list) \
    remove_head(list)

#define RemoveAt(list, index) \
    remove_at(list, index)

#define ReplaceHead(list, data, index)                       \
    {                                                        \
        __typeof__(data) _tmp = (data);                      \
        replace_head(list, &_tmp, sizeof(__typeof__(_tmp))); \
    }

#define ReplaceLast(list, data)                              \
    {                                                        \
        __typeof__(data) _tmp = (data);                      \
        replace_last(list, &_tmp, sizeof(__typeof__(_tmp))); \
    }

#define ReplaceAt(list, data, index)                              \
    {                                                             \
        __typeof__(data) _tmp = (data);                           \
        replace_at(list, &_tmp, index, sizeof(__typeof__(_tmp))); \
    }

// return a copy of the Node referred to the head element of the list
#define GetHead(list) \
    get_head(list)

// return a copy of the Node referred to the last element of the list
#define GetLast(list) \
    get_last(list)

// anche qua scrivo un if ternario e ciclo tutta la lista finche non trovo
#define Get(list, index) \
    get(list, index)

// ((list) == NULL || (index) < 0) ? NULL : ({                              \
//     typeof((list)->head) node = (list)->head;                            \
//     int i = 0;                                                           \
//     while (node->next != NULL && i < (index))                            \
//     {                                                                    \
//         node = node->next;                                               \
//         i++;                                                             \
//     }                                                                    \
//     (node == NULL) ? NULL : (*(typeof((list)->head->data))(node->data)); \
// }))

#define PrintList(list) \
    print_list(list)

#define Size(list) \
    size(list)

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

// definisco ToLower() per le stringhe quella già esistente funziona solamente per i singoli caratteri
#define ToLower(s) \
    tolower_str(s)

#define GetStrTypeOf(T) #T

#define GetListTypeOf(list) \
    get_list_type(list)

// dichiarazione opaca del nodo e della lista
typedef struct Node
{
    struct Node *prev;
    void *data;
    struct Node *next;
} Node;
typedef struct LinkedList LinkedList;

LinkedList *CreateList(size_t data_size, char *data_type);

bool insert_at(LinkedList *, void *, int, size_t);
bool add_first(LinkedList *, void *, size_t);
bool add(LinkedList *, void *, bool);
bool set_head(LinkedList *, void *, char *data_type);
bool clear(LinkedList *);
bool remove_last(LinkedList *);
bool remove_head(LinkedList *);
bool remove_at(LinkedList *, int);
bool replace_head(LinkedList *, void *, size_t);
bool replace_last(LinkedList *, void *, size_t);
bool replace_at(LinkedList *, void *, int, size_t);
void print_list(LinkedList *);
Node *get_head(LinkedList *);
Node *get_last(LinkedList *);
Node *get(LinkedList *, size_t);
char *get_list_type(LinkedList *);
int size(LinkedList *);
char *tolower_str(const char *);

#endif
