#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

// il nome della variabile lo dichairo così per evitare che l'utente utilizzi lo stesso nome
// per un'altra variabile
#define newLinkedList(type) \
    CreateList(sizeof(type), #type)
// CreateList(sizeof(type), #type, (type *)malloc(sizeof(type)))

#define InsertAt(list, data, index)     \
    {                                   \
        __typeof__(data) _tmp = (data); \
        insert_at(list, &_tmp, index);  \
    }

#define AddFirst(list, data)            \
    {                                   \
        __typeof__(data) _tmp = (data); \
        add_first(list, &_tmp);         \
    }

#define Add(list, data)                 \
    {                                   \
        __typeof__(data) _tmp = (data); \
        add(list, &_tmp);               \
    }

// #define SetHead(list, data) \
//     set_head(list, data)

// #define RemoveLast(list) \
//     remove_last(list)

// #define RemoveHead(list) \
//     remove_head(list)

// #define RemoveAt(list, index) \
//     remove_at(list, index)

// #define ReplaceHead(list, data, index)  \
//     {                                   \
//         __typeof__(data) _tmp = (data); \
//         replace_head(list, &_tmp);      \
//     }

// #define ReplaceLast(list, data)         \
//     {                                   \
//         __typeof__(data) _tmp = (data); \
//         replace_last(list, &_tmp);      \
//     }

// #define ReplaceAt(list, data, index)    \
//     {                                   \
//         __typeof__(data) _tmp = (data); \
//         replace_at(list, &_tmp, index); \
//     }

// return a copy of the Node referred to the head element of the list
// #define GetHeadNode(list) \
//     get_head_node(list)

// return a copy of the Node referred to the last element of the list
// #define GetLastNode(list) \
//     get_last_node(list)

// anche qua scrivo un if ternario e ciclo tutta la lista finche non trovo
// #define GetNode(list, index) \
//     get_node(list, index)

// #define PrintList(list) \
//     print_list(list)

// #define Size(list) \
//     size(list)

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

// definisco ToLower() per le stringhe quella già esistente funziona solamente per i singoli caratteri
// #define ToLower(s) \
//     tolower_str(s)

// #define GetListTypeOf(list) \
//     get_list_type(list)

// dichiarazione opaca del nodo e della lista
typedef struct Node
{
    struct Node *prev;
    void *data;
    struct Node *next;
} Node;
typedef struct LinkedList LinkedList;

LinkedList *CreateList(size_t, char *);

bool insert_at(LinkedList *, void *, unsigned int); // usare la macro
bool add_first(LinkedList *, void *); // usare la macro
bool add(LinkedList *, void *); // usare la macro
bool set_head(LinkedList *, void *);
bool remove_last(LinkedList *);
bool remove_head(LinkedList *);
bool remove_at(LinkedList *, unsigned int);
bool replace_head(LinkedList *, void *);
bool replace_last(LinkedList *, void *);
bool replace_at(LinkedList *, void *, unsigned int);
void print_list(LinkedList *);
Node *get_head_node(LinkedList *);
Node *get_last_node(LinkedList *);
Node *get_node(LinkedList *, size_t);
char *get_list_type(LinkedList *);
int size(LinkedList *);
char *tolower_str(const char *);

bool Clear(LinkedList *);

#endif /* _LINKEDLIST_H_ */
