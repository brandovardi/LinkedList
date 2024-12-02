#include "LinkedList.h"

LinkedList *newLinkedList(DataType data_type)
{
    LinkedList *list = NULL;
    if (data_type == INT || data_type == FLOAT || data_type == DOUBLE || data_type == CHAR || data_type == STRING)
    {
        list = (LinkedList *)malloc(sizeof(LinkedList));
        list->head = NULL;
        list->data_type = data_type;
        if (data_type == INT)
            list->data_size = sizeof(int);
        else if (data_type == FLOAT)
            list->data_size = sizeof(float);
        else if (data_type == DOUBLE)
            list->data_size = sizeof(double);
        else if (data_type == CHAR)
            list->data_size = sizeof(char);
        else if (data_type == STRING)
            list->data_size = sizeof(char *);
    }
    else if (data_type != INT && data_type != FLOAT && data_type != DOUBLE && data_type != CHAR && data_type != STRING)
        printf("Error: data_type is not valid\n");
    return list;
}

bool add_at_index(LinkedList *list, void *data, int index, size_t data_size)
{
    bool res = false;
    if (list != NULL && data != NULL && list->data_size == data_size && index >= 0)
    {
        if (list->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        Node *curr = list->head;
        int cnt;
        // se l'utente ha inserito un numero più grande rispetto alla dimensione della lista
        // non mi interessa e glielo faccio inserire alla fine, dopo l'ultimo
        for (cnt = 0; (cnt < index) && (curr->next != NULL); curr = curr->next, cnt++)
            ;
        // se l'utente vuole inserire l'elemento in posizione zero
        if (curr == list->head)
            res = add_in_front(list, data, data_size);
        // se invece vuole inserirlo alla fine
        else if (curr->next == NULL)
            res = add(list, data, data_size);
        // infine se vuole inserirlo in una posizione intermedia
        else
        {
            newNode->next = curr->next;
            curr->next = newNode;
            res = true;
        }
    }
    else if (list == NULL || data == NULL || list->data_size != data_size || index < 0)
        printf("Error: empty list or invalid data or invalid index.\n");
    return res;
}

bool add_in_front(LinkedList *list, void *data, size_t data_size)
{
    bool res = false;
    if (list != NULL && data != NULL && list->data_size == data_size)
    {
        if (list->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        // controllo se la testa esiste, quindi se la lista ha già un elemento
        // se ha già una testa allora il newNode deve diventare la testa quindi
        // faccio puntare al suo ->next la testa che sarebbe ora il primo elemento
        // così che la testa diventi il secondo elemento
        (list->head == NULL) ? (newNode->next = NULL) : (newNode->next = list->head);
        // aggiorno in ogni caso la testa
        list->head = newNode;
        res = true;
    }
    else
        printf("Error: empty list or invalid data.\n");
    return res;
}

bool add(LinkedList *list, void *data, size_t data_size)
{
    bool res = false;
    if (list != NULL && data != NULL && list->data_size == data_size)
    {
        if (list->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(list->data_size);
        memcpy(newNode->data, data, list->data_size);
        newNode->next = NULL;

        if (list->head == NULL)
            list->head = newNode;
        else
        {
            Node *curr = list->head;
            while (curr->next != NULL)
                curr = curr->next;
            curr->next = newNode;
        }
        res = true;
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
        Node *curr = list->head;
        // controllo prima che la lista abbia almeno 2 elementi
        // quindi se curr->next esiste
        if (curr->next != NULL)
            // mi serve controllare se il successivo, al successivo di quello corrente sia nullo
            // perché se voglio eliminare l'ultimo devo avere accesso al penultimo nodo
            // per fare curr->next = NULL;
            while (curr->next->next != NULL)
                curr = curr->next;
        // se la lista ha solo un elemento, quindi esiste soltanto la testa
        if (curr == list->head)
            res = remove_head(list);
        else
        {
            free(curr->next->data);
            free(curr->next);
            curr->next = NULL;
            res = true;
        }
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
            free(list->head);
            list->head = NULL;
        }
        // se invece ha più di un elemento
        else
        {
            // mi salvo il secondo elemento della lista
            Node *headNext = list->head->next;
            // svuoto la testa e la elimino
            free(list->head->data);
            free(list->head);
            // assegno alla testa il secondo elemento, che è diventato il primo
            list->head = headNext;
        }
        res = true;
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
        else if (index >= SizeOf(list) - 1)
            res = remove_last(list);
        // infine se vuole eliminare un elemento nel mezzo
        else
        {
            int cnt;
            Node *curr = list->head;
            // controllo che la lista abbia almeno due elemento prima di iniziare il ciclo
            if (list->head->next != NULL)
                for (cnt = 0; (curr->next->next != NULL) && (cnt < index - 1); curr = curr->next, cnt++)
                    ;
            // inizio a svuotare il dato
            free(curr->next->data);
            // mi salvo l'elemento da eliminare
            Node *del = curr->next;
            // modifico la lista eliminando l'elemento desiderato
            curr->next = curr->next->next;
            // infine libero la memoria dell'elemento eliminato
            free(del);
            res = true;
        }
    }
    else if (list != NULL || list->head == NULL || index < 0)
        printf("Error: empty list or invalid index.\n");
    return res;
}

bool free_list(LinkedList *list)
{
    bool res = false;
    if (list != NULL && list->head != NULL)
    {
        Node *curr = list->head;
        while (curr->next != NULL)
        {
            Node *next = curr->next;
            free(curr->data);
            free(curr);
            curr = next;
        }
        free(list);
        res = true;
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
        if (list->data_type == STRING)
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

bool replace_at(LinkedList *list, void *data, int index, size_t data_size)
{
    bool res = false;
    if (list != NULL && list->head != NULL && index >= 0 && list->data_size == data_size)
    {
        if (list->data_type == STRING)
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
            curr->data = malloc(data_size);
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
            if (list->data_type == INT)
                printf("%d\n", *(int *)curr->data);
            else if (list->data_type == FLOAT)
                printf("%f\n", *(float *)curr->data);
            else if (list->data_type == DOUBLE)
                printf("%lf\n", *(double *)curr->data);
            else if (list->data_type == STRING)
                printf("%s\n", (char *)curr->data);
            else if (list->data_type == CHAR)
                printf("%c\n", *(char *)curr->data);
            curr = curr->next;
        }
    }
    else if (list != NULL || list->head == NULL)
        printf("Error: the list is empty\n");
}

int size_of(LinkedList *list)
{
    int size = 0;
    if (list != NULL && list->head != NULL)
    {
        for (Node *curr = list->head; curr->next != NULL; curr = curr->next, size++)
            ;
        size++;
    }
    else if (list != NULL || list->head == NULL)
        printf("Error: the list is empty\n");
    return size;
}
