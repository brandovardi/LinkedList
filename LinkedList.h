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

LinkedList *CreateList(size_t data_size, char *data_type);

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
void *get_head(LinkedList *);
void *get_last(LinkedList *);
void *get(LinkedList *);
int size(LinkedList *);
size_t size_of(const char *);
char *tolower_str(char *);

#define newLinkedList(type) \
    CreateList(sizeof(type), #type)

#define InsertAt(this, data, index) \
    __typeof__(data) _tmp = (data); \
    insert_at(this, &_tmp, index, sizeof(data))

#define AddFirst(this, data)        \
    __typeof__(data) _tmp = (data); \
    add_first(this, &_tmp, sizeof(data))

#define Add(this, data)             \
    __typeof__(data) _tmp = (data); \
    add(this, &_tmp, sizeof(data))

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

#define GetHead(this) \
    get_head(this)

// non creo la funzione get_head(...) perché avendo un tipo generico per i valori della lista
// dovrei ritornare un puntatore void (castato poi al tipo di data_type della lista)
// quindi voglio evitare che un poi io mi debba gestire i puntatori dal main
// così facendo invece vado a prendere direttamente il valore contenuto
#define GetLast(this) \
    get_last(this)

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

// definisco una mia typeof perché quella presente in ctype.h non ritorna una stringa come valore
// ma restituisce direttamente il tipo, quindi per aver la possibilità di controllare
// i tipo di variabili (come il tipo dei valori inseriti nella lista generica), ho dovuto
// usare una define che si espande con _Generic() che accetta come primo parametro il tipo
// del parametro passato (quindi T in questo caso), e per ogni tipo restituisco la corrispondente
// stringa
#define TypeOf(T) _Generic((T),                     \
    char: "char",                                   \
    char *: "char *",                               \
    char **: "char **",                             \
    signed char: "signed char",                     \
    signed char *: "signed char *",                 \
    signed char **: "signed char **",               \
    unsigned char: "unsigned char",                 \
    unsigned char *: "unsigned char *",             \
    unsigned char **: "unsigned char **",           \
    short: "short",                                 \
    short *: "short *",                             \
    short **: "short **",                           \
    unsigned short: "unsigned short",               \
    unsigned short *: "unsigned short *",           \
    unsigned short **: "unsigned short **",         \
    int: "int",                                     \
    int *: "int *",                                 \
    int **: "int **",                               \
    unsigned int: "unsigned int",                   \
    unsigned int *: "unsigned int *",               \
    unsigned int **: "unsigned int **",             \
    long: "long",                                   \
    long *: "long *",                               \
    long **: "long **",                             \
    unsigned long: "unsigned long",                 \
    unsigned long *: "unsigned long *",             \
    unsigned long **: "unsigned long **",           \
    long long: "long long",                         \
    long long *: "long long *",                     \
    long long **: "long long **",                   \
    unsigned long long: "unsigned long long",       \
    unsigned long long *: "unsigned long long *",   \
    unsigned long long **: "unsigned long long **", \
    float: "float",                                 \
    float *: "float *",                             \
    float **: "float **",                           \
    double: "double",                               \
    double *: "double *",                           \
    double **: "double **",                         \
    long double: "long double",                     \
    long double *: "long double *",                 \
    long double **: "long double **",               \
    LinkedList: "LinkedList",                       \
    LinkedList *: "LinkedList *",                   \
    LinkedList **: "LinkedList **",                 \
    Node: "Node",                                   \
    Node *: "Node *",                               \
    Node **: "Node **",                             \
    void *: "void *",                               \
    default: "unknown")

// definisco una sizeof che accetta come parametro una stringa del tipo da verificare (es. "char")
#define SizeOf(T) \
    size_of(T)

// definisco ToLower() per le stringhe quella già esistente funziona solamente per i singoli caratteri
#define ToLower(s) \
    tolower_str(s)

#endif
