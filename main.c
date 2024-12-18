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

    Add(list, 1);
    Add(list, 2);
    Add(list, 90);

    char *g = "gg";
    char *c = "c";
    char *l = "l";
    Add(l1, c);
    Add(l1, g);
    Add(l1, "y");
    PrintList(l1);
    ReplaceHead(l1, "ciao");
    PrintList(l1);
    ReplaceLast(l1, "ciaoo");
    Add(l1, "nuovo");
    PrintList(l1);
    RemoveLast(l1);
    PrintList(l1);
    RemoveAt(l1, 1);
    PrintList(l1);

    char *asd = "asd";
    Add(l1, asd);
    PrintList(l1);

    Add(l2, m1);
    Add(l3, (Moto *)malloc(sizeof(Moto)));
    PrintList(l3);

    const Node *f = get_node(list, size(list) - 1);
    const int fdata = *(int *)f->data;
    printf("%d\n", fdata);
    PrintList(list);
    FreeList(list);
    print_list(list);

    free(m1);

    return EXIT_SUCCESS;
}