#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

// Il tipo passato viene forzato a essere un puntatore valido, garantendo un controllo implicito del tipo.
#define newLinkedList(type) \
    CreateList(sizeof(*((type *)0)), #type)

#define InsertAt(list, data, index)                                \
    {                                                              \
        __typeof__(data) _tmp = (data);                            \
        insert_at(CheckList(list), &_tmp, index, GetTypeOf(_tmp)); \
    }

#define AddFirst(list, data)                                \
    {                                                       \
        __typeof__(data) _tmp = (data);                     \
        add_first(CheckList(list), &_tmp, GetTypeOf(_tmp)); \
    }

#define AddLast(list, data)                                \
    {                                                      \
        __typeof__(data) _tmp = (data);                    \
        add_last(CheckList(list), &_tmp, GetTypeOf(_tmp)); \
    }

#define Remove(list, index) \
    remove_at(CheckList(list), index)

#define Set(list, data, index)                               \
    {                                                        \
        __typeof__(data) _tmp = (data);                      \
        set(CheckList(list), &_tmp, index, GetTypeOf(_tmp)); \
    }

#define PeekFirst(list) \
    peek_first(CheckList(list))

#define PeekLast(list) \
    peek_last(CheckList(list))

#define GetNode(list, index) \
    get_node(CheckList(list), index)

#define Get(list, index) \
    get(CheckList(list), index)

#define Peek(list) \
    peek(CheckList(list))

#define Pop(list) \
    pop(CheckList(list))

#define PrintList(list) \
    print_list(CheckList(list))

#define Size(list) \
    size(CheckList(list))

#define IndexOf(list, data)                                \
    {                                                      \
        __typeof__(data) _tmp = (data);                    \
        index_of(CheckList(list), &_tmp, GetTypeOf(_tmp)); \
    }

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

#define CheckList(list) \
    (SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL))

#define NULL_LIST printf("Exception - List is NULL.\n")
#define EMPTY_LIST printf("Exception - List has no element.\n")
#define NULL_DATA printf("Exception - Data is NULL.\n")
#define INVALID_DATA_TYPE printf("Exception - Data Type is not valid.\n")
#define INDEX_OUT_OF_BOUND printf("Exception - Index Out Of Bound.\n")

typedef struct Node
{
    struct Node *prev;
    void *data;
    struct Node *next;
} Node;

typedef struct LinkedList LinkedList;

LinkedList *CreateList(size_t, char *);

// insert a generic element in the list
void insert_at(LinkedList *, void *, size_t, char *); // use the macro
// add an element in front of the list
void add_first(LinkedList *, void *, char *);         // use the macro
// append an element at the end of the list
void add_last(LinkedList *, void *, char *);          // use the macro
// remove an element in the list at the specified index
void remove_at(LinkedList *, size_t);
// replace an element in the list at the specified index
void set(LinkedList *, void *, size_t, char *); // use the macro
// attemtp to print the list
void print_list(LinkedList *);
// return the node of the list from the given index
Node *get_node(LinkedList *, size_t);
// return the void * of the element at the specified index
void *get(LinkedList *, size_t);
// simply return the first element of the list
void *peek_first(LinkedList *);
// simply return the last element of the list
void *peek_last(LinkedList *);
// remove and return the last element of the list
void *pop(LinkedList *);
// return the size of the list, so the number of elements contained
size_t size(LinkedList *);
// return the index (if exist) of the element you want to find in the list
int index_of(LinkedList *, void *, char *);

// deallocate (free) all the memory assigned to the list
void FreeList(LinkedList *);

#define DECLARE_TYPE(type)                          \
    type:                                           \
    #type,                                          \
        type * : #type " *",                        \
                 type ** : #type " **",             \
                           type *** : #type " ***", \
                                      type **** : #type " ****"

#define BASE_TYPES(T) _Generic((T),   \
    DECLARE_TYPE(char),               \
    DECLARE_TYPE(signed char),        \
    DECLARE_TYPE(unsigned char),      \
    DECLARE_TYPE(short),              \
    DECLARE_TYPE(unsigned short),     \
    DECLARE_TYPE(int),                \
    DECLARE_TYPE(unsigned int),       \
    DECLARE_TYPE(long),               \
    DECLARE_TYPE(unsigned long),      \
    DECLARE_TYPE(long long),          \
    DECLARE_TYPE(unsigned long long), \
    DECLARE_TYPE(float),              \
    DECLARE_TYPE(double),             \
    DECLARE_TYPE(long double),        \
    DECLARE_TYPE(Node),               \
    void *: "void *",                 \
    void **: "void **",               \
    void ****: "void ****",           \
    default: "undefined")

#ifdef USER_TYPES
#define GetTypeOf(T) _Generic((T), \
    USER_TYPES,                    \
    default: BASE_TYPES(T))
#else
#define GetTypeOf(T) BASE_TYPES(T)
#endif

#endif /* _LINKEDLIST_H */
