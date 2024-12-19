#define USER_TYPES DECLARE_TYPE(Macchina), DECLARE_TYPE(Moto)
#include "LinkedList.h"

typedef struct Macchina
{
    int tipo;
} Macchina;

typedef struct Moto
{
    int tipo;
} Moto;

int main(int argc, char const *argv[])
{
    LinkedList *list = newLinkedList(int);
    LinkedList *l2 = newLinkedList(Macchina *);
    LinkedList *l3 = newLinkedList(Moto *);
    LinkedList *l1 = newLinkedList(char *);
    LinkedList *l4 = newLinkedList(LinkedList *);
    Macchina *m1 = (Macchina *)malloc(sizeof(Macchina));

    AddLast(list, 1);
    AddLast(list, 2);
    AddLast(list, 90);

    char *g = "gg";
    char *c = "c";
    char *l = "l";
    AddLast(l1, c);
    AddLast(l1, g);
    AddLast(l1, "y");
    
    PrintList(l1);
    Set(l1, "ciao", 0);
    PrintList(l1);
    Set(l1, "ciaoo", Size(list));
    AddLast(l1, "nuovo");
    PrintList(l1);
    Remove(l1, Size(list));
    PrintList(l1);
    Remove(l1, 1);
    PrintList(l1);

    char *asd = "asd";
    AddLast(l1, asd);
    PrintList(l1);

    int qwer = *(int *)Pop(list);
    printf("qwer: %d\n", qwer);

    AddLast(l2, m1);
    AddLast(l3, (Moto *)malloc(sizeof(Moto)));
    PrintList(l3);

    const Node *f = GetNode(list, Size(list) - 1);
    const int fdata = *(int *)f->data;
    printf("%d\n", fdata);
    PrintList(list);
    FreeList(list);
    PrintList(list);

    free(m1);

    return EXIT_SUCCESS;
}