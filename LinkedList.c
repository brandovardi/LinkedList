#include "LinkedList.h"

typedef struct LinkedList
{
    struct Node *head;
    struct Node *last;
    size_t size;
    size_t data_size; // Dimensione di ogni elemento
    char *data_type;
} LinkedList;

LinkedList *CreateList(size_t data_size, char *data_type)
{
    LinkedList *list = NULL;
    if (data_type != NULL)
    {
        data_type = tolower_str(data_type);
        list = (LinkedList *)malloc(sizeof(LinkedList));
        list->head = NULL;
        list->last = NULL;
        list->size = 0;
        list->data_type = data_type;
        list->data_size = data_size;
    }
    else
        printf("Error: data_type is not valid\n");
    return list;
}

bool insert_at(LinkedList *list, void *data, unsigned int index, char *data_type)
{
    bool res = false;
    if (list->head == NULL)
    {
        res = set_head(list, data);
    }
    // SameType(*(__typeof(*(list->head->data)) *)list->head->data, *data)
    else if (list != NULL && data != NULL && SameType(*list->head->data, *data) && index >= 0)
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        Node *curr = list->head;
        int cnt;
        // se l'utente ha inserito un numero più grande rispetto alla dimensione della lista
        // non mi interessa e glielo faccio inserire alla fine, dopo l'ultimo
        for (cnt = 0; (cnt < index) && (curr->next != NULL); curr = curr->next, cnt++)
            ;
        // se l'utente vuole inserire l'elemento in posizione zero
        if (curr == list->head)
            res = add_first(list, data, data_type);
        // se invece vuole inserirlo alla fine
        else if (curr->next == NULL)
            res = add(list, data, data_type);
        // infine se vuole inserirlo in una posizione intermedia
        else
        {
            newNode->prev = curr;
            newNode->next = curr->next;
            curr->next = newNode;
            res = true;
        }
        (!res) ?: (list->size++);
    }
    else
        printf("Error: empty list or invalid data or invalid index.\n");
    return res;
}

bool add_first(LinkedList *list, void *data, char *data_type)
{
    bool res = false;
    if (list->head == NULL)
    {
        res = set_head(list, data);
    }
    if (list != NULL && data != NULL && SameType(*list->head->data, *data))
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;
        memcpy(newNode->data, data, list->data_size);
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
        res = true;
        list->size++;
    }
    else
        printf("Error: empty list or invalid data.\n");
    return res;
}

bool add(LinkedList *list, void *data, char *data_type)
{
    bool res = false;
    if (list->head == NULL)
    {
        res = set_head(list, data);
    }
    else if (list != NULL && data != NULL && !strcmp(list->data_type, data_type))
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        newNode->prev = list->last;    // assgno al prec del nuovo nodo l'ultimo della lista
        list->last->next = newNode;    // assegno al successivo dell'ultimo, il nuovo nodo
        list->last = list->last->next; // faccio diventare il nuovo nodo l'ultimo della lista

        res = true;
        list->size++;
    }
    else
        printf("Error: empty list or invalid data.\n");
    return res;
}

bool set_head(LinkedList *list, void *data)
{
    bool res = false;
    
    if (list != NULL && list->head == NULL && !strcmp(list->data_type, GetTypeOf(*data)))
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        list->head = newNode;
        list->last = list->head;

        list->size++;
        res = true;
    }

    return res;
}

bool remove_last(LinkedList *list)
{
    bool res = false;
    if (list != NULL && list->head != NULL)
    {
        Node *last = list->last;
        // se la lista ha solo un elemento, quindi esiste soltanto la testa
        if (list->last == list->head)
            res = remove_head(list);
        else
        {
            list->last = list->last->prev;
            free(list->last->next);
            list->last->next = NULL;
            free(last->data);
            last->data = NULL;
            free(last->prev);
            last->prev = NULL;
            free(last);
            last = NULL;
            res = true;
        }
        (res && list->size > 0) ? (list->size--) : 0;
    }
    else
        printf("Error: the list is empty\n");
    return res;
}

bool remove_head(LinkedList *list)
{
    bool res = false;
    if (list != NULL && list->head != NULL)
    {
        // se la lista ha soltanto un elemento, quindi ha soltanto la testa
        if (list->head->next == NULL)
        {
            free(list->head->data);
            list->head->data = NULL;
            free(list->head);
            list->head = NULL;
            free(list->last);
            list->last = NULL;
        }
        // se invece ha più di un elemento
        else
        {
            // mi salvo il secondo elemento della lista
            Node *headNext = list->head->next;
            // svuoto la testa e la elimino
            free(list->head->data);
            list->head->data = NULL;
            free(list->head);
            // assegno alla testa il secondo elemento, che è diventato il primo
            list->head = headNext;
            free(list->head->prev);
            list->head->prev = NULL;
        }
        res = true;
        (list->size <= 0) ?: (list->size--);
    }
    else
        printf("Error: the list is empty\n");
    return res;
}

bool remove_at(LinkedList *list, unsigned int index)
{
    bool res = false;
    if (list != NULL && list->head != NULL && index >= 0)
    {
        // controllo subito se vuole eliminare la testa, quindi se index == 0
        if (!index)
            res = remove_head(list);
        // e controlo subito anche se vuole eliminare l'ultimo elemento
        else if (index >= size(list) - 1)
            res = remove_last(list);
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
            res = true;
        }
        (res && list->size > 0) ? (list->size--) : 0;
    }
    else
        printf("Error: empty list or invalid index.\n");
    return res;
}

bool replace_head(LinkedList *list, void *data)
{
    bool res = false;
    if (list != NULL && list->head != NULL && SameType(*list->head->data, *data))
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        free(list->head->data);
        list->head->data = NULL;
        list->head->data = malloc(list->data_size);
        memcpy(list->head->data, data, list->data_size);
        res = true;
    }
    else
        printf("Error while replacing the head of the list.\n");
    return res;
}

bool replace_last(LinkedList *list, void *data)
{
    bool res = false;
    if (list != NULL && list->last != NULL && SameType(*list->head->data, *data))
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        free(list->last->data);
        list->last->data = NULL;
        list->last->data = malloc(list->data_size);
        memcpy(list->last->data, data, list->data_size);
        res = true;
    }
    else
        printf("Error while replacing the last element of the list.\n");
    return res;
}

bool replace_at(LinkedList *list, void *data, unsigned int index)
{
    bool res = false;
    if (list != NULL && list->head != NULL && index >= 0 && SameType(*list->head->data, *data))
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        if (!index)
            res = replace_head(list, data);
        else
        {
            int i;
            Node *curr;
            for (curr = list->head, i = 0; (i < index) && (curr->next != NULL); curr = curr->next, i++)
                ;
            free(curr->data);
            curr->data = NULL;
            curr->data = malloc(list->data_size);
            memcpy(curr->data, data, list->data_size);
            res = true;
        }
    }
    else
        printf("Error while replacing element in the list.\n");
    return res;
}

void print_list(LinkedList *list)
{
    if (list != NULL && list->head != NULL)
    {
        Node *curr = list->head;
        while (curr != NULL)
        {
            if (strstr(list->data_type, "*"))
            {
                // qua ho puntatori
            }
            else
            {
                // qui ho i tipi base
                if (!strcmp(list->data_type, "int"))
                    printf("%d\n", *(__typeof__(list->data_type) *)curr->data);
                else if (!strcmp(list->data_type, "float"))
                    printf("%f\n", *(__typeof__(list->data_type) *)curr->data);
                else if (!strcmp(list->data_type, "double"))
                    printf("%g\n", *(__typeof__(list->data_type) *)curr->data);
                else if (!strcmp(list->data_type, "char"))
                    printf("%c\n", *(__typeof__(list->data_type) *)curr->data);
                else if (!strcmp(list->data_type, "unsigned int"))
                    printf("%u\n", *(__typeof__(list->data_type) *)curr->data);
            }

            curr = curr->next;
        }
    }
    else
        printf("Error: the list is empty\n");
}

Node *get_head_node(LinkedList *list)
{
    Node *newHead;
    if (list != NULL && list->head != NULL)
    {
        newHead = (Node *)malloc(sizeof(Node));
        newHead->next = NULL;
        newHead->prev = NULL;
        newHead->data = malloc(list->data_size);
        memcpy(newHead->data, list->head->data, list->data_size);
    }
    else
        newHead = NULL;

    return newHead;
}

Node *get_last_node(LinkedList *list)
{
    Node *newLast;
    if (list != NULL && list->last != NULL)
    {
        newLast = (Node *)malloc(sizeof(Node));
        newLast->next = NULL;
        newLast->prev = NULL;
        newLast->data = malloc(list->data_size);
        memcpy(newLast->data, list->last->data, list->data_size);
        if (!strcmp(list->data_type, "char"))
            newLast->data = *(char **)newLast->data;
    }
    else
        newLast = NULL;

    return newLast;
}

Node *get_node(LinkedList *list, size_t index)
{
    Node *curr = NULL;
    int i;
    if (list != NULL && list->head != NULL)
    {
        if (!index)
        {
            curr = get_head_node(list);
        }
        else if (index == size(list) - 1)
        {
            curr = get_last_node(list);
        }
        else
        {
            curr = list->head;
            for (i = 0; i < index && curr->next != NULL; curr = curr->next, i++)
                ;
                }
    }
    return curr;
}

int size(LinkedList *list)
{
    int size = 0;
    (list != NULL) ? (size = list->size) : printf("Error: the list doesn't exist.\n");
    return size;
}

char *tolower_str(const char *str)
{
    int l = strlen(str) + 1;

    // Allocazione dinamica della memoria per la nuova stringa (più 1 per '\0')
    char *lower_str = (char *)malloc(l * sizeof(char));

    if (lower_str == NULL)
    {
        printf("malloc failed.\n");
        lower_str = NULL;
    }
    else
    {
        for (int i = 0; i < l; i++)
            *(lower_str + i) = tolower((unsigned char)*(str + i));
        *(lower_str + l) = '\0';
    }
    return lower_str;
}

char *get_list_type(LinkedList *list)
{
    return (list == NULL) ? "NULL" : list->data_type;
}

bool Clear(LinkedList *list)
{
    bool res = false;
    if (list != NULL && list->head != NULL)
    {
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
        res = true;
        list->size = 0;
    }
    else
        printf("Error: the list is empty\n");

    return res;
}
