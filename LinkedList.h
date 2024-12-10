#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

// Il type passato viene forzato a essere un puntatore valido, garantendo un controllo implicito del tipo.
#define newLinkedList(type) \
    CreateList(sizeof(*((type *)0)), #type)

#define InsertAt(list, data, index)                                                             \
    {                                                                                           \
        __typeof__(data) _tmp = (data);                                                         \
        insert_at((SameType(list, LinkedList *) ? list : NULL), &_tmp, index, __my_tmp_type__); \
    }

#define AddFirst(list, data)                                                             \
    {                                                                                    \
        __typeof__(data) _tmp = (data);                                                  \
        add_first((SameType(list, LinkedList *) ? list : NULL), &_tmp, __my_tmp_type__); \
    }

#define Add(list, data)                                                                                                        \
    {                                                                                                                          \
        __typeof__(data) _tmp = (data);                                                                                        \
        Node *head = get_head_node(list);                                                                                      \
        add((SameType(list, LinkedList *) ? list : NULL), &_tmp, SameType(*(__typeof__(_tmp) *)head->data, __typeof__(_tmp))); \
    }

// add(list, &_tmp, GetTypeOf(_tmp)); \

// #define SetHead(list, data) \
//     set_head(list, data)

// #define RemoveLast(list) \
//     remove_last(list)

// #define RemoveHead(list) \
//     remove_head(list)

// #define RemoveAt(list, index) \
//     remove_at(list, index)

#define ReplaceHead(list, data, index)                                                      \
    {                                                                                       \
        __typeof__(data) _tmp = (data);                                                     \
        replace_head((SameType(list, LinkedList *) ? list : NULL), &_tmp, GetTypeOf(_tmp)); \
    }

#define ReplaceLast(list, data)                                                             \
    {                                                                                       \
        __typeof__(data) _tmp = (data);                                                     \
        replace_last((SameType(list, LinkedList *) ? list : NULL), &_tmp, GetTypeOf(_tmp)); \
    }

#define ReplaceAt(list, data, index)                                                             \
    {                                                                                            \
        __typeof__(data) _tmp = (data);                                                          \
        replace_at((SameType(list, LinkedList *) ? list : NULL), &_tmp, index, GetTypeOf(_tmp)); \
    }

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

typedef struct Node
{
    struct Node *prev;
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList LinkedList;

LinkedList *CreateList(size_t, char *);

bool insert_at(LinkedList *, void *, unsigned int, char *); // usare la macro
bool add_first(LinkedList *, void *, char *);               // usare la macro
bool add(LinkedList *, void *, char *);                     // usare la macro
bool set_head(LinkedList *, void *);
bool remove_last(LinkedList *);
bool remove_head(LinkedList *);
bool remove_at(LinkedList *, unsigned int);
bool replace_head(LinkedList *, void *, char *);
bool replace_last(LinkedList *, void *, char *);
bool replace_at(LinkedList *, void *, unsigned int, char *);
void print_list(LinkedList *);
Node *get_head_node(LinkedList *);
Node *get_last_node(LinkedList *);
Node *get_node(LinkedList *, size_t);
char *get_list_type(LinkedList *);
int size(LinkedList *);

bool Clear(LinkedList *);

char *tolower_str(const char *);

#define GetTypeOf(T) _Generic((T),                    \
    char: "char",                                     \
    signed char: "signed char",                       \
    unsigned char: "unsigned char",                   \
    short: "short",                                   \
    unsigned short: "unsigned short",                 \
    int: "int",                                       \
    unsigned int: "unsigned int",                     \
    long: "long",                                     \
    unsigned long: "unsigned long",                   \
    long long: "long long",                           \
    unsigned long long: "unsigned long long",         \
    float: "float",                                   \
    double: "double",                                 \
    long double: "long double",                       \
    char *: "char *",                                 \
    signed char *: "signed char *",                   \
    unsigned char *: "unsigned char *",               \
    short *: "short *",                               \
    unsigned short *: "unsigned short *",             \
    int *: "int *",                                   \
    unsigned int *: "unsigned int *",                 \
    long *: "long *",                                 \
    unsigned long *: "unsigned long *",               \
    long long *: "long long *",                       \
    unsigned long long *: "unsigned long long *",     \
    float *: "float *",                               \
    double *: "double *",                             \
    long double *: "long double *",                   \
    char **: "char **",                               \
    signed char **: "signed char **",                 \
    unsigned char **: "unsigned char **",             \
    short **: "short **",                             \
    unsigned short **: "unsigned short **",           \
    int **: "int **",                                 \
    unsigned int **: "unsigned int **",               \
    long **: "long **",                               \
    unsigned long **: "unsigned long **",             \
    long long **: "long long **",                     \
    unsigned long long **: "unsigned long long **",   \
    float **: "float **",                             \
    double **: "double **",                           \
    long double **: "long double **",                 \
    char ***: "char ***",                             \
    signed char ***: "signed char ***",               \
    unsigned char ***: "unsigned char ***",           \
    short ***: "short ***",                           \
    unsigned short ***: "unsigned short ***",         \
    int ***: "int ***",                               \
    unsigned int ***: "unsigned int ***",             \
    long ***: "long ***",                             \
    unsigned long ***: "unsigned long ***",           \
    long long ***: "long long ***",                   \
    unsigned long long ***: "unsigned long long ***", \
    float ***: "float ***",                           \
    double ***: "double ***",                         \
    long double ***: "long double ***",               \
    void *: "void *",                                 \
    void **: "void **",                               \
    void ***: "void ***",                             \
    Node: "Node",                                     \
    Node *: "Node *",                                 \
    default: "undefined")

#endif /* _LINKEDLIST_H_ */
