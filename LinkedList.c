#include "LinkedList.h"
#include "Exception.h"

// implementing the list in the .c file to avoid exposing the list structure
// it would be like making the list structure "private"
typedef struct LinkedList
{
    struct Node *head;
    struct Node *last;
    size_t size;
    size_t data_size; // Size of each element
    char *data_type;
} LinkedList;

void validateList(char *, LinkedList *, char *, size_t, char *, bool, bool, bool, bool);
void validateMemoryAllocation(void *);

static bool init_head(LinkedList *, void *);
static void set_head(LinkedList *, void *, char *);
static void set_last(LinkedList *, void *, char *);
static void remove_last(LinkedList *);
static void remove_first(LinkedList *);
static Node *get_head_node(LinkedList *);
static Node *get_last_node(LinkedList *);

void validateMemoryAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("malloc failed!");
        printStackTrace();
        exit(EXIT_FAILURE);
    }
}

LinkedList *CreateList(size_t data_size, char *data_type)
{
    if ((data_type == NULL || !strcmp(data_type, "")) || data_size == 0)
    {
        fprintf(stderr, "Error while creating the list!\nPossible errors: invalid data type or data size.\nExiting...\n");
        printStackTrace();
        exit(EXIT_FAILURE);
    }
    LinkedList *list = NULL;
    list = (LinkedList *)malloc(sizeof(LinkedList));
    validateMemoryAllocation(list);
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
    list->data_type = data_type;
    list->data_size = data_size;
    return list;
}

void insert_at(LinkedList *list, void *data, size_t index, char *data_type)
{
    validateList("insert_at()", list, data, index, data_type, false, true, true, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
        newNode->next = NULL;
        newNode->prev = NULL;

        Node *curr = list->head;
        int cnt;
        for (cnt = 0; (cnt < index) && (curr->next != NULL); curr = curr->next, cnt++)
            ;
        // if the user wants to insert the element at position zero
        if (curr == list->head)
            add_first(list, data, data_type);
        // if instead he wants to insert it at the end
        else if (curr->next == NULL)
            add_last(list, data, data_type);
        // finally if he wants to insert it in an intermediate position
        else
        {
            newNode->prev = curr;
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
}

void add_first(LinkedList *list, void *data, char *data_type)
{
    validateList("add_first()", list, data, 0, data_type, false, true, false, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        newNode->next = NULL;
        newNode->prev = NULL;
        memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
        // check if the head exists, so if the list already has an element
        // if it already has a head then the newNode must become the head so
        // make its ->next point to the head which would now be the first element
        // so that the head becomes the second element
        if (list->head == NULL)
        {
            list->head = newNode;
            list->last = list->head;
        }
        else
        {
            newNode->next = list->head;
            list->head = newNode;
        }
        list->size++;
    }
}

void add_last(LinkedList *list, void *data, char *data_type)
{
    validateList("add_last()", list, data, 0, data_type, false, true, false, true);

    if (list->head == NULL)
        init_head(list, data);
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
        newNode->next = NULL;
        newNode->prev = NULL;

        newNode->prev = list->last;    // assign the previous of the new node to the last of the list
        list->last->next = newNode;    // assign the next of the last to the new node
        list->last = list->last->next; // make the new node the last of the list

        list->size++;
    }
}

static bool init_head(LinkedList *list, void *data)
{
    validateList("init_head()", list, data, 0, NULL, false, true, false, false);

    Node *newNode = (Node *)malloc(sizeof(Node));
    validateMemoryAllocation(newNode);
    newNode->data = malloc(list->data_size);
    validateMemoryAllocation(newNode->data);
    memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    newNode->next = NULL;
    newNode->prev = NULL;

    list->head = newNode;
    list->last = list->head;

    list->size++;
}

static void remove_last(LinkedList *list)
{
    validateList("remove_at()->remove_last()", list, NULL, 0, NULL, true, false, false, false);

    Node *last = list->last;
    // if the list has only one element, so there is only the head
    if (list->last == list->head)
        remove_first(list);
    else
    {
        list->last = list->last->prev;
        list->last->next = NULL;
        free(last->data);
        free(last);
        (list->size <= 0) ?: (list->size--);
    }
}

static void remove_first(LinkedList *list)
{
    validateList("remove_at()->remove_first()", list, NULL, 0, NULL, true, false, false, false);

    // if the list has only one element, so there is only the head
    if (list->head->next == NULL)
    {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->last = NULL;
        list->size = 0;
    }
    // if instead it has more than one element
    else
    {
        // save the second element of the list
        Node *head = list->head;
        // clear the head and delete it
        list->head = list->head->next;
        list->head->prev = NULL;
        free(head->data);
        free(head);
        (list->size <= 0) ?: (list->size--);
    }
}

void remove_at(LinkedList *list, size_t index)
{
    validateList("remove_at()", list, NULL, index, NULL, true, false, true, false);

    // immediately check if the user wants to delete the head, so if index == 0
    if (!index)
        remove_first(list);
    // and also immediately check if the user wants to delete the last element
    else if (index >= list->size - 1)
        remove_last(list);
    // finally if the user wants to delete an element in the middle
    else
    {
        int cnt;
        Node *curr = list->head;
        for (cnt = 0; (curr->next != NULL) && (cnt < index); curr = curr->next, cnt++)
            ;
        // start clearing the data
        free(curr->data);
        // modify the list by deleting the desired element
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        curr->next = NULL;
        curr->prev = NULL;
        // finally free the memory of the deleted element
        free(curr);
        curr = NULL;
        (list->size <= 0) ?: (list->size--);
    }
}

static void set_head(LinkedList *list, void *data, char *data_type)
{
    validateList("set()->set_last()", list, data, 0, data_type, true, true, false, true);

    list->head->data = realloc(list->head->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    validateMemoryAllocation(list->head->data);
    memcpy(list->head->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
}

static void set_last(LinkedList *list, void *data, char *data_type)
{
    validateList("set()->set_last()", list, data, 0, data_type, true, true, false, true);

    list->last->data = realloc(list->last->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    validateMemoryAllocation(list->last->data);
    memcpy(list->last->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
}

void set(LinkedList *list, void *data, size_t index, char *data_type)
{
    validateList("set()", list, data, index, data_type, true, true, true, true);

    if (!index)
        set_head(list, data, data_type);
    else if (index == list->size - 1)
        set_last(list, data, data_type);
    else
    {
        int i;
        Node *curr;
        for (curr = list->head, i = 0; (i < index) && (curr->next != NULL); curr = curr->next, i++)
            ;
        free(curr->data);
        curr->data = NULL;
        curr->data = malloc(list->data_size);
        validateMemoryAllocation(curr->data);
        memcpy(curr->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    }
}

void print_list(LinkedList *list)
{
    validateList("print_list()", list, NULL, 0, NULL, false, false, false, false);

    Node *curr = list->head;
    int i = 0;
    printf("List elements:\n");
    while (curr != NULL)
    {
        // qui ho i tipi base
        if (!strcmp(list->data_type, "char"))
            printf("%c\n", *(char *)curr->data);
        else if (!strcmp(list->data_type, "signed char"))
            printf("%hhd\n", *(signed char *)curr->data);
        else if (!strcmp(list->data_type, "unsigned char"))
            printf("%hhu\n", *(unsigned char *)curr->data);
        else if (!strcmp(list->data_type, "short"))
            printf("%hd\n", *(short *)curr->data);
        else if (!strcmp(list->data_type, "unsigned short"))
            printf("%hu\n", *(unsigned short *)curr->data);
        else if (!strcmp(list->data_type, "int"))
            printf("%d\n", *(int *)curr->data);
        else if (!strcmp(list->data_type, "unsigned int"))
            printf("%u\n", *(unsigned int *)curr->data);
        else if (!strcmp(list->data_type, "long"))
            printf("%ld\n", *(long *)curr->data);
        else if (!strcmp(list->data_type, "unsigned long"))
            printf("%lu\n", *(unsigned long *)curr->data);
        else if (!strcmp(list->data_type, "long long"))
            printf("%lld\n", *(long long *)curr->data);
        else if (!strcmp(list->data_type, "unsigned long long"))
            printf("%llu\n", *(unsigned long long *)curr->data);
        else if (!strcmp(list->data_type, "float"))
            printf("%f\n", *(float *)curr->data);
        else if (!strcmp(list->data_type, "double"))
            printf("%lf\n", *(double *)curr->data);
        else if (!strcmp(list->data_type, "long double"))
            printf("%Lf\n", *(long double *)curr->data);
        else
            printf("%d- %s: 0x%0llX\n", ++i, list->data_type, curr->data);

        curr = curr->next;
    }
    if (list->size == 0)
        printf("List is empty.\n");
}

static Node *get_head_node(LinkedList *list)
{
    validateList("get_node()->get_head_node()", list, NULL, 0, NULL, true, false, false, false);

    Node *newHead = NULL;
    newHead = (Node *)malloc(sizeof(Node));
    validateMemoryAllocation(newHead);
    newHead->next = NULL;
    newHead->prev = NULL;
    newHead->data = malloc(list->data_size);
    validateMemoryAllocation(newHead->data);
    memcpy(newHead->data, list->head->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)list->head->data) + 1) : list->data_size));

    return newHead;
}

static Node *get_last_node(LinkedList *list)
{
    validateList("get_node()->get_last_node()", list, NULL, 0, NULL, true, false, false, false);

    Node *newLast = NULL;
    newLast = (Node *)malloc(sizeof(Node));
    validateMemoryAllocation(newLast);
    newLast->next = NULL;
    newLast->prev = NULL;
    newLast->data = malloc(list->data_size);
    validateMemoryAllocation(newLast->data);
    memcpy(newLast->data, list->last->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)list->head->data) + 1) : list->data_size));

    return newLast;
}

Node *get_node(LinkedList *list, size_t index)
{
    validateList("get_node()", list, NULL, index, NULL, true, false, true, false);

    Node *newNode = NULL;
    Node *curr = NULL;
    int i;
    if (!index)
        newNode = get_head_node(list);
    else if (index == list->size - 1)
        newNode = get_last_node(list);
    else
    {
        curr = list->head;
        for (i = 0; i < index && curr->next != NULL; curr = curr->next, i++)
            ;
        newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        memcpy(newNode->data, curr->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)list->head->data) + 1) : list->data_size));
    }

    return newNode;
}

void *peek_first(LinkedList *list)
{
    validateList("get()->get_head()", list, NULL, 0, NULL, true, false, false, false);
    return list->head->data;
}

void *peek_last(LinkedList *list)
{
    validateList("get()->get_last()", list, NULL, 0, NULL, true, false, false, false);
    return list->last->data;
}

void *get(LinkedList *list, size_t index)
{
    validateList("get()", list, NULL, index, NULL, true, false, true, false);

    void *data = NULL;
    int i;
    if (!index)
        data = peek_first(list);
    else if (index == list->size - 1)
        data = peek_last(list);
    else
    {
        Node *curr = list->head;
        for (i = 0; i < index && curr->next != NULL; curr = curr->next, i++)
            ;
        data = curr->data;
    }
    return data;
}

void *pop(LinkedList *list)
{
    validateList("pop()", list, NULL, 0, NULL, true, false, false, false);

    void *last = malloc(sizeof(void));
    memcpy(last, list->last->data, list->data_size);
    
    remove_last(list);

    return last;
}

size_t size(LinkedList *list)
{
    return (list != NULL) ? (list->size) : (NULL_LIST, 0);
}

// this function works only with primitive types
int index_of(LinkedList *list, void *data, char *data_type)
{
    validateList("index_of()", list, data, 0, data_type, true, true, false, true);
    int index = -1;

    int i;
    Node *curr = list->head;
    for (i = 0; curr->next != NULL && index != i; curr = curr->next, i++)
    {
        if (index == -1)
            if ((!strcmp(list->data_type, "char") && *(char *)curr->data == *(char *)data)
                || (!strcmp(list->data_type, "signed char") && *(signed char *)curr->data == *(signed char *)data)
                || (!strcmp(list->data_type, "unsigned char") && *(unsigned char *)curr->data == *(unsigned char *)data)
                || (!strcmp(list->data_type, "short") && *(short *)curr->data == *(short *)data)
                || (!strcmp(list->data_type, "unsigned short") && *(unsigned short *)curr->data == *(unsigned short *)data)
                || (!strcmp(list->data_type, "int") && *(int *)curr->data == *(int *)data)
                || (!strcmp(list->data_type, "unsigned int") && *(unsigned int *)curr->data == *(unsigned int *)data)
                || (!strcmp(list->data_type, "long") && *(long *)curr->data == *(long *)data)
                || (!strcmp(list->data_type, "unsigned long") && *(unsigned long *)curr->data == *(unsigned long *)data)
                || (!strcmp(list->data_type, "long long") && *(long long *)curr->data == *(long long *)data)
                || (!strcmp(list->data_type, "unsigned long long") && *(unsigned long long *)curr->data == *(unsigned long long *)data)
                || (!strcmp(list->data_type, "float") && *(float *)curr->data == *(float *)data)
                || (!strcmp(list->data_type, "double") && *(double *)curr->data == *(double *)data)
                || (!strcmp(list->data_type, "long double") && *(long double*)curr->data == *(long double *)data))
                index = i;
    }

    return index;
}

void FreeList(LinkedList *list)
{
    validateList("FreeList()", list, NULL, 0, NULL, true, false, false, false);

    Node *curr = list->head;
    while (curr != NULL)
    {
        Node *next = curr->next;
        free(curr->data);
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
}

void validateList(char *funName, LinkedList *list, char *data, size_t index, char *datatype, bool checkhead, bool is_data, bool is_index, bool is_datatype)
{
    bool check = false;
    if (list == NULL || (checkhead && list->head == NULL))
    {
        (list == NULL) ? NULL_LIST : EMPTY_LIST;
        fprintf(stderr, "Invalid List! Exiting...\n");
        check = true;
    }
    if (is_data && data == NULL)
    {
        NULL_DATA;
        fprintf(stderr, "Invalid Data! Exiting...\n");
        check = true;
    }
    if (is_index && index > list->size)
    {
        INDEX_OUT_OF_BOUND;
        fprintf(stderr, "Invalid Index! Exiting...\n");
        check = true;
    }
    if (is_datatype && (datatype == NULL || strcmp(list->data_type, datatype)))
    {
        INVALID_DATA_TYPE;
        fprintf(stderr, "Invalid Data Type! Exiting...\n");
        check = true;
    }
    if (check)
    {
        printf("Exception from: %s; ", funName);
        printStackTrace();
        exit(EXIT_FAILURE);
    }
}
