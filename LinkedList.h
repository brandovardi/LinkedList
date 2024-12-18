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

#define InsertAt(list, data, index)                                                                                 \
    {                                                                                                               \
        __typeof__(data) _tmp = (data);                                                                             \
        insert_at((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, index, GetTypeOf(_tmp)); \
    }

#define AddFirst(list, data)                                                                                 \
    {                                                                                                        \
        __typeof__(data) _tmp = (data);                                                                      \
        add_first((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, GetTypeOf(_tmp)); \
    }

#define Add(list, data)                                                                                \
    {                                                                                                  \
        __typeof__(data) _tmp = (data);                                                                \
        add((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, GetTypeOf(_tmp)); \
    }

#define RemoveLast(list) \
    remove_last((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

#define RemoveHead(list) \
    remove_head((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

#define RemoveAt(list, index) \
    remove_at((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), index)

#define ReplaceHead(list, data)                                                                                 \
    {                                                                                                           \
        __typeof__(data) _tmp = (data);                                                                         \
        replace_head((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, GetTypeOf(_tmp)); \
    }

#define ReplaceLast(list, data)                                                                                 \
    {                                                                                                           \
        __typeof__(data) _tmp = (data);                                                                         \
        replace_last((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, GetTypeOf(_tmp)); \
    }

#define ReplaceAt(list, data, index)                                                                                 \
    {                                                                                                                \
        __typeof__(data) _tmp = (data);                                                                              \
        replace_at((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), &_tmp, index, GetTypeOf(_tmp)); \
    }

#define GetHeadNode(list) \
    get_head_node((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

#define GetLastNode(list) \
    get_last_node((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : NULL))

#define GetNode(list, index) \
    get_node((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)), index)

#define PrintList(list) \
    print_list((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

#define Size(list) \
    size((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

#define SameType(a, b) \
    (__builtin_types_compatible_p(__typeof__(a), __typeof__(b)))

#define GetListTypeOf(list) \
    get_list_type((SameType(list, LinkedList *) ? ((LinkedList *)(list)) : (NULL)))

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

void insert_at(LinkedList *, void *, size_t, char *); // usare la macro
void add_first(LinkedList *, void *, char *);         // usare la macro
void add(LinkedList *, void *, char *);               // usare la macro
void remove_last(LinkedList *);
void remove_head(LinkedList *);
void remove_at(LinkedList *, size_t);
void replace_head(LinkedList *, void *, char *);       // usare la macro
void replace_last(LinkedList *, void *, char *);       // usare la macro
void replace_at(LinkedList *, void *, size_t, char *); // usare la macro
void print_list(LinkedList *);
Node *get_head_node(LinkedList *);
Node *get_last_node(LinkedList *);
Node *get_node(LinkedList *, size_t);
char *get_list_type(LinkedList *);
int size(LinkedList *);

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
