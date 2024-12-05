#include "LinkedList.h"

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

LinkedList *CreateList(size_t data_size, char *data_type)
{
    LinkedList *list = NULL;
    if (data_type != NULL)
    {
        data_type = ToLower(data_type);
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

bool insert_at(LinkedList *list, void *data, int index, size_t data_size)
{
    bool res = false;
    if (list != NULL && data != NULL && list->data_size == data_size && index >= 0)
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
            res = add_first(list, data, data_size);
        // se invece vuole inserirlo alla fine
        else if (curr->next == NULL)
            res = add(list, data, data_size);
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
    else if (list == NULL || data == NULL || list->data_size != data_size || index < 0)
        printf("Error: empty list or invalid data or invalid index.\n");
    return res;
}

bool add_first(LinkedList *list, void *data, size_t data_size)
{
    bool res = false;
    if (list != NULL && data != NULL && list->data_size == data_size)
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

bool add(LinkedList *list, void *data, bool same_type)
{
    bool res = false;

    if (list != NULL && data != NULL && same_type)
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        if (list->head == NULL)
        {
            list->head = newNode;
            list->last = list->head;
        }
        else
        {
            newNode->prev = list->last;    // assgno al prec del nuovo nodo l'ultimo della lista
            list->last->next = newNode;    // assegno al successivo dell'ultimo, il nuovo nodo
            list->last = list->last->next; // faccio diventare il nuovo nodo l'ultimo della lista
        }
        res = true;
        list->size++;
    }
    else
        printf("Error: empty list or invalid data.\n");
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
    else if (list != NULL || list->head == NULL)
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
    else if (list != NULL || list->head == NULL)
        printf("Error: the list is empty\n");
    return res;
}

bool remove_at(LinkedList *list, int index)
{
    bool res = false;
    if (list != NULL && list->head != NULL && index >= 0)
    {
        // controllo subito se vuole eliminare la testa, quindi se index == 0
        if (!index)
            res = remove_head(list);
        // e controlo subito anche se vuole eliminare l'ultimo elemento
        else if (index >= Size(list) - 1)
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
    else if (list != NULL || list->head == NULL || index < 0)
        printf("Error: empty list or invalid index.\n");
    return res;
}

bool clear(LinkedList *list)
{
    bool res = false;
    if (list != NULL && list->head != NULL)
    {
        Node *curr = list->head;
        while (curr->next != NULL)
        {
            Node *next = curr->next;
            free(curr->data);
            curr->data = NULL;
            free(curr);
            curr = NULL;
            curr->prev = NULL;
            curr = next;
        }
        free(list);
        list->head = NULL;
        list->last = NULL;
        res = true;
        list->size = 0;
    }
    else if (list != NULL || list->head == NULL)
        printf("Error: the list is empty\n");
    return res;
}

bool replace_head(LinkedList *list, void *data, size_t data_size)
{
    bool res = false;
    if (list != NULL && list->head != NULL && list->data_size == data_size)
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

bool replace_last(LinkedList *list, void *data, size_t data_size)
{
    bool res = false;
    if (list != NULL && list->last != NULL && list->data_size == data_size)
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

bool replace_at(LinkedList *list, void *data, int index, size_t data_size)
{
    bool res = false;
    if (list != NULL && list->head != NULL && index >= 0 && list->data_size == data_size)
    {
        if (!strcmp(list->data_type, "char *"))
            data = *(char **)data;
        if (!index)
            res = replace_head(list, data, data_size);
        else
        {
            int i;
            Node *curr;
            for (curr = list->head, i = 0; (i < index) && (curr->next != NULL); curr = curr->next, i++)
                ;
            free(curr->data);
            curr->data = NULL;
            curr->data = malloc(list->data_size);
            memcpy(curr->data, data, data_size);
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
                if (!strcmp(list->data_type, "float"))
                    printf("%f\n", *(__typeof__(list->data_type) *)curr->data);
                if (!strcmp(list->data_type, "double"))
                    printf("%g\n", *(__typeof__(list->data_type) *)curr->data);
                if (!strcmp(list->data_type, "char"))
                    printf("%c\n", *(__typeof__(list->data_type) *)curr->data);
                if (!strcmp(list->data_type, "unsigned int"))
                    printf("%u\n", *(__typeof__(list->data_type) *)curr->data);
            }

            curr = curr->next;
        }
    }
    else if (list != NULL || list->head == NULL)
        printf("Error: the list is empty\n");
}

void *get_head(LinkedList *list)
{
    return (list == NULL || list->head == NULL) ? NULL : (list->head->data);
}

void *get_last(LinkedList *list)
{
    return (list == NULL || list->last == NULL) ? NULL : (list->last->data);
}

void *get(LinkedList *list, size_t index)
{
    if (list != NULL && list->head != NULL)
    {
        // typeof(list->head->data) res = *(list->head->data);

        // if (index == 0)
        // {
        //     res =
        // }

        // Node *curr = list->head;
    }
}

int size(LinkedList *list)
{
    int size = 0;
    (list != NULL && list->head != NULL) ? (size = list->size) : printf("Error: the list is empty.\n");
    return size;
}

size_t size_of(char *T)
{
    // int i = 0;
    size_t res = -1;
    // size_t pointer_lvl = 0;

    // char* token = strtok(T, " ");

    // // Keep printing tokens while one of the
    // // delimiters present in str[].
    // while (token != NULL && *(token+i) != '\0')
    // {
    //     if (*(token+i) == '*')
    //         pointer_lvl++;
    // }
    // if (pointer_lvl != strlen(strtok(T, " ")))

    // char
    if (!strcmp(T, "char"))
        res = sizeof(char);
    else if (!strcmp(T, "char *"))
        res = sizeof(char *);
    else if (!strcmp(T, "char **"))
        res = sizeof(char **);
    // signed char
    else if (!strcmp(T, "signed char"))
        res = sizeof(signed char);
    else if (!strcmp(T, "signed char *"))
        res = sizeof(signed char *);
    else if (!strcmp(T, "signed char **"))
        res = sizeof(signed char **);
    // unsigned char
    else if (!strcmp(T, "unsigned char"))
        res = sizeof(unsigned char);
    else if (!strcmp(T, "unsigned char *"))
        res = sizeof(unsigned char *);
    else if (!strcmp(T, "unsigned char **"))
        res = sizeof(unsigned char **);
    // short
    else if (!strcmp(T, "short"))
        res = sizeof(short);
    else if (!strcmp(T, "short *"))
        res = sizeof(short *);
    else if (!strcmp(T, "short **"))
        res = sizeof(short **);
    // short int
    else if (!strcmp(T, "short int"))
        res = sizeof(short int);
    else if (!strcmp(T, "short int *"))
        res = sizeof(short int *);
    else if (!strcmp(T, "short int **"))
        res = sizeof(short int **);
    // signed short
    else if (!strcmp(T, "signed short"))
        res = sizeof(signed short);
    else if (!strcmp(T, "signed short *"))
        res = sizeof(signed short *);
    else if (!strcmp(T, "signed short **"))
        res = sizeof(signed short **);
    // signed short int
    else if (!strcmp(T, "signed short int"))
        res = sizeof(signed short int);
    else if (!strcmp(T, "signed short int *"))
        res = sizeof(signed short int *);
    else if (!strcmp(T, "signed short int **"))
        res = sizeof(signed short int **);
    // unsigned short
    else if (!strcmp(T, "unsigned short"))
        res = sizeof(unsigned short);
    else if (!strcmp(T, "unsigned short *"))
        res = sizeof(unsigned short *);
    else if (!strcmp(T, "unsigned short **"))
        res = sizeof(unsigned short **);
    // unsigned short int
    else if (!strcmp(T, "unsigned short int"))
        res = sizeof(unsigned short int);
    else if (!strcmp(T, "unsigned short int *"))
        res = sizeof(unsigned short int *);
    else if (!strcmp(T, "unsigned short int **"))
        res = sizeof(unsigned short int **);
    // int
    else if (!strcmp(T, "int"))
        res = sizeof(int);
    else if (!strcmp(T, "int *"))
        res = sizeof(int *);
    else if (!strcmp(T, "int **"))
        res = sizeof(int **);
    else if (!strcmp(T, "signed"))
        res = sizeof(signed);
    else if (!strcmp(T, "singed *"))
        res = sizeof(signed *);
    else if (!strcmp(T, "signed **"))
        res = sizeof(signed **);
    else if (!strcmp(T, "signed int"))
        res = sizeof(signed int);
    else if (!strcmp(T, "signed int *"))
        res = sizeof(signed int *);
    else if (!strcmp(T, "signed int **"))
        res = sizeof(signed int **);
    else if (!strcmp(T, "unsigned int"))
        res = sizeof(unsigned int);
    else if (!strcmp(T, "unsigned int *"))
        res = sizeof(unsigned int *);
    else if (!strcmp(T, "unsigned int **"))
        res = sizeof(unsigned int **);
    else if (!strcmp(T, "long"))
        res = sizeof(long);
    else if (!strcmp(T, "long *"))
        res = sizeof(long *);
    else if (!strcmp(T, "long **"))
        res = sizeof(long **);
    else if (!strcmp(T, "long int"))
        res = sizeof(long int);
    else if (!strcmp(T, "long int *"))
        res = sizeof(long int *);
    else if (!strcmp(T, "long int **"))
        res = sizeof(long int **);
    else if (!strcmp(T, "unsigned long"))
        res = sizeof(unsigned long);
    else if (!strcmp(T, "unsigned long *"))
        res = sizeof(unsigned long *);
    else if (!strcmp(T, "unsigned long **"))
        res = sizeof(unsigned long **);
    else if (!strcmp(T, "long long"))
        res = sizeof(long long);
    else if (!strcmp(T, "long long *"))
        res = sizeof(long long *);
    else if (!strcmp(T, "long long **"))
        res = sizeof(long long **);
    else if (!strcmp(T, "unsigned long long"))
        res = sizeof(unsigned long long);
    else if (!strcmp(T, "unsigned long long *"))
        res = sizeof(unsigned long long *);
    else if (!strcmp(T, "unsigned long long **"))
        res = sizeof(unsigned long long **);
    else if (!strcmp(T, "float"))
        res = sizeof(float);
    else if (!strcmp(T, "float *"))
        res = sizeof(float *);
    else if (!strcmp(T, "float **"))
        res = sizeof(float **);
    else if (!strcmp(T, "double"))
        res = sizeof(double);
    else if (!strcmp(T, "double *"))
        res = sizeof(double *);
    else if (!strcmp(T, "double **"))
        res = sizeof(double **);
    else if (!strcmp(T, "long double"))
        res = sizeof(long double);
    else if (!strcmp(T, "long double *"))
        res = sizeof(long double *);
    else if (!strcmp(T, "long double **"))
        res = sizeof(long double **);
    else if (!strcmp(T, "LinkedList"))
        res = sizeof(LinkedList);
    else if (!strcmp(T, "LinkedList *"))
        res = sizeof(LinkedList *);
    else if (!strcmp(T, "LinkedList **"))
        res = sizeof(LinkedList **);
    else if (!strcmp(T, "Node"))
        res = sizeof(Node);
    else if (!strcmp(T, "Node *"))
        res = sizeof(Node *);
    else if (!strcmp(T, "Node **"))
        res = sizeof(Node **);
    else if (!strcmp(T, "size_t"))
        res = sizeof(size_t);
    else if (!strcmp(T, "size_t *"))
        res = sizeof(size_t *);
    else if (!strcmp(T, "size_t **"))
        res = sizeof(size_t **);
    else if (!strcmp(T, "void *"))
        res = sizeof(void *);
    else
        printf("Error: unknown type.\n");

    return res;
}

char *tolower_str(const char *str)
{
    int l = strlen(str) + 1;

    // Allocazione dinamica della memoria per la nuova stringa (più 1 per '\0')
    char *lower_str = (char *)malloc(l * SizeOf("char"));

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
