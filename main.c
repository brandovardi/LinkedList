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
    Macchina *m1 = (Macchina *)malloc(sizeof(Macchina));

    Add(l1, "mia sottostringa");
    char * g = "gg";
    Add(l1, g);
    PrintList(l1);

    Add(l2, m1);
    Add(l3, (Moto *)malloc(sizeof(Moto)));
    PrintList(l3);

    Add(list, 1);
    Add(list, 2);
    Add(list, 90);

    const Node *f = get_node(list, size(list) - 1);
    const int fdata = *(int *)f->data;
    printf("%d\n", fdata);
    PrintList(list);
    FreeList(list);
    print_list(list);

    free(m1);

    return EXIT_SUCCESS;
}