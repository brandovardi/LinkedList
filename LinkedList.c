#include "LinkedList.h"

LinkedList *newLinkedList(DataType data_type)
{
    LinkedList *this = NULL;
    if (data_type == INT || data_type == FLOAT || data_type == DOUBLE || data_type == CHAR || data_type == STRING)
    {
        this = (LinkedList *)malloc(sizeof(LinkedList));
        this->head = NULL;
        this->last = NULL;
        this->size = 0;
        this->data_type = data_type;
        if (data_type == INT)
            this->data_size = sizeof(int);
        else if (data_type == FLOAT)
            this->data_size = sizeof(float);
        else if (data_type == DOUBLE)
            this->data_size = sizeof(double);
        else if (data_type == CHAR)
            this->data_size = sizeof(char);
        else if (data_type == STRING)
            this->data_size = sizeof(char *);
    }
    else if (data_type != INT && data_type != FLOAT && data_type != DOUBLE && data_type != CHAR && data_type != STRING)
        printf("Error: data_type is not valid\n");
    return this;
}

bool insert_at(LinkedList *this, void *data, int index, size_t data_size)
{
    bool res = false;
    if (this != NULL && data != NULL && this->data_size == data_size && index >= 0)
    {
        if (this->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(this->data_size);
        memcpy(newNode->data, data, this->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        Node *curr = this->head;
        int cnt;
        // se l'utente ha inserito un numero più grande rispetto alla dimensione della lista
        // non mi interessa e glielo faccio inserire alla fine, dopo l'ultimo
        for (cnt = 0; (cnt < index) && (curr->next != NULL); curr = curr->next, cnt++)
            ;
        // se l'utente vuole inserire l'elemento in posizione zero
        if (curr == this->head)
            res = add_first(this, data, data_size);
        // se invece vuole inserirlo alla fine
        else if (curr->next == NULL)
            res = add(this, data, data_size);
        // infine se vuole inserirlo in una posizione intermedia
        else
        {
            newNode->prev = curr;
            newNode->next = curr->next;
            curr->next = newNode;
            res = true;
        }
        (!res) ?: (this->size++);
    }
    else if (this == NULL || data == NULL || this->data_size != data_size || index < 0)
        printf("Error: empty list or invalid data or invalid index.\n");
    return res;
}

bool add_first(LinkedList *this, void *data, size_t data_size)
{
    bool res = false;
    if (this != NULL && data != NULL && this->data_size == data_size)
    {
        if (this->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(this->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;
        memcpy(newNode->data, data, this->data_size);
        // controllo se la testa esiste, quindi se la lista ha già un elemento
        // se ha già una testa allora il newNode deve diventare la testa quindi
        // faccio puntare al suo ->next la testa che sarebbe ora il primo elemento
        // così che la testa diventi il secondo elemento
        if (this->head == NULL)
        {
            this->head = newNode;
            this->last = this->head;
        }
        else
        {
            newNode->next = this->head;
            this->head = newNode;
        }
        res = true;
        this->size++;
    }
    else
        printf("Error: empty list or invalid data.\n");
    return res;
}

bool add(LinkedList *this, void *data, size_t data_size)
{
    bool res = false;
    if (this != NULL && data != NULL && this->data_size == data_size)
    {
        if (this->data_type == STRING)
            data = *(char **)data;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = malloc(this->data_size);
        memcpy(newNode->data, data, this->data_size);
        newNode->next = NULL;
        newNode->prev = NULL;

        if (this->head == NULL)
        {
            this->head = newNode;
            this->last = this->head;
        }
        else
        {
            newNode->prev = this->last;    // assgno al prec del nuovo nodo l'ultimo della lista
            this->last->next = newNode;    // assegno al successivo dell'ultimo, il nuovo nodo
            this->last = this->last->next; // faccio diventare il nuovo nodo l'ultimo della lista
        }
        res = true;
        this->size++;
    }
    else
        printf("Error: empty list or invalid data.\n");
    return res;
}

bool remove_last(LinkedList *this)
{
    bool res = false;
    if (this != NULL && this->head != NULL)
    {
        Node *last = this->last;
        // se la lista ha solo un elemento, quindi esiste soltanto la testa
        if (this->last == this->head)
            res = remove_head(this);
        else
        {
            this->last = this->last->prev;
            free(this->last->next);
            this->last->next = NULL;
            free(last->data);
            last->data = NULL;
            free(last->prev);
            last->prev = NULL;
            free(last);
            last = NULL;
            res = true;
        }
        (res && this->size > 0) ? (this->size--) : 0;
    }
    else if (this != NULL || this->head == NULL)
        printf("Error: the list is empty\n");
    return res;
}

bool remove_head(LinkedList *this)
{
    bool res = false;
    if (this != NULL && this->head != NULL)
    {
        // se la lista ha soltanto un elemento, quindi ha soltanto la testa
        if (this->head->next == NULL)
        {
            free(this->head->data);
            this->head->data = NULL;
            free(this->head);
            this->head = NULL;
            free(this->last);
            this->last = NULL;
        }
        // se invece ha più di un elemento
        else
        {
            // mi salvo il secondo elemento della lista
            Node *headNext = this->head->next;
            // svuoto la testa e la elimino
            free(this->head->data);
            this->head->data = NULL;
            free(this->head);
            // assegno alla testa il secondo elemento, che è diventato il primo
            this->head = headNext;
            free(this->head->prev);
            this->head->prev = NULL;
        }
        res = true;
        (this->size <= 0) ?: (this->size--);
    }
    else if (this != NULL || this->head == NULL)
        printf("Error: the list is empty\n");
    return res;
}

bool remove_at(LinkedList *this, int index)
{
    bool res = false;
    if (this != NULL && this->head != NULL && index >= 0)
    {
        // controllo subito se vuole eliminare la testa, quindi se index == 0
        if (!index)
            res = remove_head(this);
        // e controlo subito anche se vuole eliminare l'ultimo elemento
        else if (index >= SizeOf(this) - 1)
            res = remove_last(this);
        // infine se vuole eliminare un elemento nel mezzo
        else
        {
            int cnt;
            Node *curr = this->head;
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
        (res && this->size > 0) ? (this->size--) : 0;
    }
    else if (this != NULL || this->head == NULL || index < 0)
        printf("Error: empty list or invalid index.\n");
    return res;
}

bool clear(LinkedList *this)
{
    bool res = false;
    if (this != NULL && this->head != NULL)
    {
        Node *curr = this->head;
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
        free(this);
        this->head = NULL;
        this->last = NULL;
        res = true;
        this->size = 0;
    }
    else if (this != NULL || this->head == NULL)
        printf("Error: the list is empty\n");
    return res;
}

bool replace_head(LinkedList *this, void *data, size_t data_size)
{
    bool res = false;
    if (this != NULL && this->head != NULL && this->data_size == data_size)
    {
        if (this->data_type == STRING)
            data = *(char **)data;
        free(this->head->data);
        this->head->data = NULL;
        this->head->data = malloc(this->data_size);
        memcpy(this->head->data, data, this->data_size);
        res = true;
    }
    else
        printf("Error while replacing the head of the list.\n");
    return res;
}

bool replace_at(LinkedList *this, void *data, int index, size_t data_size)
{
    bool res = false;
    if (this != NULL && this->head != NULL && index >= 0 && this->data_size == data_size)
    {
        if (this->data_type == STRING)
            data = *(char **)data;
        if (!index)
            res = replace_head(this, data, data_size);
        else
        {
            int i;
            Node *curr;
            for (curr = this->head, i = 0; (i < index) && (curr->next != NULL); curr = curr->next, i++)
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

void print_list(LinkedList *this)
{
    if (this != NULL && this->head != NULL)
    {
        Node *curr = this->head;
        while (curr != NULL)
        {
            if (this->data_type == INT)
                printf("%d\n", *(int *)curr->data);
            else if (this->data_type == FLOAT)
                printf("%f\n", *(float *)curr->data);
            else if (this->data_type == DOUBLE)
                printf("%lf\n", *(double *)curr->data);
            else if (this->data_type == STRING)
                printf("%s\n", (char *)curr->data);
            else if (this->data_type == CHAR)
                printf("%c\n", *(char *)curr->data);
            curr = curr->next;
        }
    }
    else if (this != NULL || this->head == NULL)
        printf("Error: the list is empty\n");
}

int size_of(LinkedList *this)
{
    int size = 0;
    (this != NULL && this->head != NULL) ? (size = this->size) : printf("Error: the list is empty.\n");
    return size;
}
