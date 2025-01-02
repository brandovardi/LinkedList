#define USER_TYPES DECLARE_TYPE(Car), DECLARE_TYPE(Bike)
#include "LinkedList.h"

typedef struct Car
{
    int tipo;
} Car;

typedef struct Bike
{
    int tipo;
} Bike;

int main(int argc, char const *argv[])
{
    LinkedList *list = newLinkedList(int);
    LinkedList *l2 = newLinkedList(Car);
    LinkedList *l3 = newLinkedList(Bike *);
    LinkedList *l1 = newLinkedList(char *);
    LinkedList *l4 = newLinkedList(LinkedList *);
    Car c1 = {.tipo = 1};

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
    Set(l1, "hello", 0);
    PrintList(l1);
    Set(l1, "helloo", Size(list));
    AddLast(l1, "newElement");
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

    AddLast(l2, c1);
    PrintList(l2);
    AddLast(l3, (Bike *)malloc(sizeof(Bike)));
    PrintList(l3);

    const Node *f = GetNode(list, Size(list) - 1);
    const int fdata = *(int *)f->data;
    printf("%d\n", fdata);
    PrintList(list);
    FreeList(list);
    PrintList(list);

    Car kl = *(Car *)PeekFirst(l2);
    printf("%d\n", kl.tipo);

    // free(c1);

    return EXIT_SUCCESS;
}