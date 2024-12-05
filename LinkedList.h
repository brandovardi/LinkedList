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

#define Add(list, data)                                                                                                          \
    {                                                                                                                            \
        __typeof__(data) _tmp = (data);                                                                                          \
        add(list, &_tmp, (list == NULL ? 0 : ((GetHead(list) == NULL && SameType(GetHead(list), data)) ? 1 : 0))); \
    }

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

#define GetHead(list) \
    *((__typeof__(get_head(list)) *)get_head(list))

// non creo la funzione get_head(...) perché avendo un tipo generico per i valori della lista
// dovrei ritornare un puntatore void (castato poi al tipo di data_type della lista)
// quindi voglio evitare che un poi io mi debba gestire i puntatori dal main
// così facendo invece vado a prendere direttamente il valore contenuto
#define GetLast(list) \
    *((__typeof__(get_last(list)) *)get_last(list))

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

// definisco una sizeof che accetta come parametro una stringa del tipo da verificare (es. "char")
#define SizeOf(T) \
    size_of(T)

// definisco ToLower() per le stringhe quella già esistente funziona solamente per i singoli caratteri
#define ToLower(s) \
    tolower_str(s)

#define GetStrTypeOf(T) #T

#define GetListTypeOf(list) \
    get_list_type(list)

// dichiarazione opaca del nodo e della lista
typedef struct Node Node;
typedef struct LinkedList LinkedList;

LinkedList *CreateList(size_t data_size, char *data_type);

bool insert_at(LinkedList *, void *, int, size_t);
bool add_first(LinkedList *, void *, size_t);
bool add(LinkedList *, void *, bool);
bool clear(LinkedList *);
bool remove_last(LinkedList *);
bool remove_head(LinkedList *);
bool remove_at(LinkedList *, int);
bool replace_head(LinkedList *, void *, size_t);
bool replace_last(LinkedList *, void *, size_t);
bool replace_at(LinkedList *, void *, int, size_t);
void print_list(LinkedList *);
void *get_head(LinkedList *);
void *get_last(LinkedList *);
void *get(LinkedList *, size_t);
char *get_list_type(LinkedList *);
int size(LinkedList *);
size_t size_of(char *);
char *tolower_str(const char *);

#endif

// definisco una mia typeof perché quella presente in ctype.h non ritorna una stringa come valore
// ma restituisce direttamente il tipo, quindi per aver la possibilità di controllare
// i tipo di variabili (come il tipo dei valori inseriti nella lista generica), ho dovuto
// usare una define che si espande con _Generic() che accetta come primo parametro il tipo
// del parametro passato (quindi T in questo caso), e per ogni tipo restituisco la corrispondente
// stringa
// #define TypeOf(T) _Generic((T),                     \
//     char: "char",                                   \
//     char *: "char *",                               \
//     char **: "char **",                             \
//     signed char: "signed char",                     \
//     signed char *: "signed char *",                 \
//     signed char **: "signed char **",               \
//     unsigned char: "unsigned char",                 \
//     unsigned char *: "unsigned char *",             \
//     unsigned char **: "unsigned char **",           \
//     short: "short",                                 \
//     short *: "short *",                             \
//     short **: "short **",                           \
//     unsigned short: "unsigned short",               \
//     unsigned short *: "unsigned short *",           \
//     unsigned short **: "unsigned short **",         \
//     int: "int",                                     \
//     int *: "int *",                                 \
//     int **: "int **",                               \
//     unsigned int: "unsigned int",                   \
//     unsigned int *: "unsigned int *",               \
//     unsigned int **: "unsigned int **",             \
//     long: "long",                                   \
//     long *: "long *",                               \
//     long **: "long **",                             \
//     unsigned long: "unsigned long",                 \
//     unsigned long *: "unsigned long *",             \
//     unsigned long **: "unsigned long **",           \
//     long long: "long long",                         \
//     long long *: "long long *",                     \
//     long long **: "long long **",                   \
//     unsigned long long: "unsigned long long",       \
//     unsigned long long *: "unsigned long long *",   \
//     unsigned long long **: "unsigned long long **", \
//     float: "float",                                 \
//     float *: "float *",                             \
//     float **: "float **",                           \
//     double: "double",                               \
//     double *: "double *",                           \
//     double **: "double **",                         \
//     long double: "long double",                     \
//     long double *: "long double *",                 \
//     long double **: "long double **",               \
//     LinkedList: "LinkedList",                       \
//     LinkedList *: "LinkedList *",                   \
//     LinkedList **: "LinkedList **",                 \
//     Node: "Node",                                   \
//     Node *: "Node *",                               \
//     Node **: "Node **",                             \
//     void *: "void *",                               \
//     default: "unknown")