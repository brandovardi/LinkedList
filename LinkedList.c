#include "LinkedList.h"
#include "Exception.h"

// implemento la lista nel .c per evitare di esporre la struttura della lista
// sarebbe come mettere "private" la struttura della lista
typedef struct LinkedList
{
    struct Node *head;
    struct Node *last;
    size_t size;
    size_t data_size; // Dimensione di ogni elemento
    char *data_type;
} LinkedList;

static bool set_head(LinkedList *, void *);
void validateList(char *, LinkedList *, char *, size_t, char *, bool, bool, bool, bool);
void validateMemoryAllocation(void *);

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
        set_head(list, data);
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
        // se l'utente vuole inserire l'elemento in posizione zero
        if (curr == list->head)
            add_first(list, data, data_type);
        // se invece vuole inserirlo alla fine
        else if (curr->next == NULL)
            add(list, data, data_type);
        // infine se vuole inserirlo in una posizione intermedia
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
    validateList("add_first()", list, data, -1, data_type, false, true, false, true);

    if (list->head == NULL)
        set_head(list, data);
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        newNode->next = NULL;
        newNode->prev = NULL;
        memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
        // controllo se la testa esiste, quindi se la lista ha già un elemento
        // se ha già una testa allora il newNode deve diventare la testa quindi
        // faccio puntare al suo ->next la testa che sarebbe ora il primo elemento
        // così che la testa diventi il secondo elemento
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

void add(LinkedList *list, void *data, char *data_type)
{
    validateList("add()", list, data, -1, data_type, false, true, false, true);

    // char *tmp = *(char **)data;
    // if (!strcmp(list->data_type, "char *"))
    //     data = *(char **)data;

    if (list->head == NULL)
        set_head(list, data);
    else
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        validateMemoryAllocation(newNode);
        newNode->data = malloc(list->data_size);
        validateMemoryAllocation(newNode->data);
        memcpy(newNode->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
        newNode->next = NULL;
        newNode->prev = NULL;

        newNode->prev = list->last;    // assgno al prec del nuovo nodo l'ultimo della lista
        list->last->next = newNode;    // assegno al successivo dell'ultimo, il nuovo nodo
        list->last = list->last->next; // faccio diventare il nuovo nodo l'ultimo della lista

        list->size++;
    }
}

static bool set_head(LinkedList *list, void *data)
{
    validateList("set_head()", list, data, -1, NULL, false, true, false, false);

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

void remove_last(LinkedList *list)
{
    validateList("remove_last()", list, NULL, -1, NULL, true, false, false, false);

    Node *last = list->last;
    // se la lista ha solo un elemento, quindi esiste soltanto la testa
    if (list->last == list->head)
        remove_head(list);
    else
    {
        list->last = list->last->prev;
        list->last->next = NULL;
        free(last->data);
        free(last);
        (list->size <= 0) ?: (list->size--);
    }
}

void remove_head(LinkedList *list)
{
    validateList("remove_head()", list, NULL, -1, NULL, true, false, false, false);

    // se la lista ha soltanto un elemento, quindi ha soltanto la testa
    if (list->head->next == NULL)
    {
        free(list->head->data);
        free(list->head);
        list->head = NULL;
        list->last = NULL;
        list->size = 0;
    }
    // se invece ha più di un elemento
    else
    {
        // mi salvo il secondo elemento della lista
        Node *head = list->head;
        // svuoto la testa e la elimino
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

    // controllo subito se vuole eliminare la testa, quindi se index == 0
    if (!index)
        remove_head(list);
    // e controlo subito anche se vuole eliminare l'ultimo elemento
    else if (index >= size(list) - 1)
        remove_last(list);
    // infine se vuole eliminare un elemento nel mezzo
    else
    {
        int cnt;
        Node *curr = list->head;
        for (cnt = 0; (curr->next != NULL) && (cnt < index); curr = curr->next, cnt++)
            ;
        // inizio a svuotare il dato
        free(curr->data);
        // modifico la lista eliminando l'elemento desiderato
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        curr->next = NULL;
        curr->prev = NULL;
        // infine libero la memoria dell'elemento eliminato
        free(curr);
        curr = NULL;
        (list->size <= 0) ?: (list->size--);
    }
}

void replace_head(LinkedList *list, void *data, char *data_type)
{
    validateList("replace_head()", list, data, -1, data_type, true, true, false, true);

    list->head->data = realloc(list->head->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    validateMemoryAllocation(list->head->data);
    memcpy(list->head->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
}

void replace_last(LinkedList *list, void *data, char *data_type)
{
    validateList("replace_last()", list, data, -1, data_type, true, true, false, true);

    list->last->data = realloc(list->last->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
    validateMemoryAllocation(list->last->data);
    memcpy(list->last->data, data, (!strcmp(list->data_type, "char *") ? (strlen((char *)data) + 1) : list->data_size));
}

void replace_at(LinkedList *list, void *data, size_t index, char *data_type)
{
    validateList("replace_at()", list, data, index, data_type, true, true, true, true);

    if (!index)
        replace_head(list, data, data_type);
    else if (index == size(list) - 1)
        replace_last(list, data, data_type);
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
    validateList("print_list()", list, NULL, -1, NULL, false, false, false, false);

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
        else if (!strcmp(list->data_type, "char *"))
            printf("0x%0llX (trying reading data from char*: %s)\n", (char **)curr->data, (char **)curr->data);
        else
            printf("%d- %s: 0x%0llX\n", ++i, list->data_type, curr->data);

        curr = curr->next;
    }
    if (list->size == 0)
        printf("List is empty.\n");
}

Node *get_head_node(LinkedList *list)
{
    validateList("get_head_node()", list, NULL, -1, NULL, true, false, false, false);

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

Node *get_last_node(LinkedList *list)
{
    validateList("get_last_node()", list, NULL, -1, NULL, true, false, false, false);

    Node *newLast = NULL;
    newLast = (Node *)malloc(sizeof(Node));
    validateMemoryAllocation(newLast);
    newLast->next = NULL;
    newLast->prev = NULL;
    newLast->data = malloc(list->data_size);
    validateMemoryAllocation(newLast->data);
    memcpy(newLast->data, list->last->data, (!strcmp(list->data_type, "char *") ? (strlen((char *)list->head->data) + 1) : list->data_size));
    if (!strcmp(list->data_type, "char"))
        newLast->data = *(char **)newLast->data;

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
    else if (index == size(list) - 1)
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

        if (!strcmp(list->data_type, "char"))
            newNode->data = *(char **)newNode->data;
    }

    return newNode;
}

int size(LinkedList *list)
{
    int size = 0;
    (list != NULL) ? (size = list->size) : NULL_LIST;
    return size;
}

char *get_list_type(LinkedList *list)
{
    return (list == NULL) ? NULL : list->data_type;
}

void FreeList(LinkedList *list)
{
    validateList("Clear()", list, NULL, -1, NULL, true, false, false, false);

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
