#define USER_TYPES DECLARE_TYPE(Macchina), DECLARE_TYPE(Moto)
#include "LinkedList.h"

typedef struct Macchina {
    int tipo;
} Macchina;

typedef struct Moto {
    int tipo;
} Moto;

int main()
{
    LinkedList *list = newLinkedList(int);
    LinkedList *l2 = newLinkedList(Macchina *);
    LinkedList *l3 = newLinkedList(Moto *);
    Macchina *m1 = (Macchina *)malloc(sizeof(Macchina));
    Moto *m2 = (Moto *)malloc(sizeof(Moto));

    Add(l2, m1);
    Add(l3, m2);

    char * s = "45";

    Add(list, 1);
    Add(list, 2);
    // Add(list, "ciao");
    Add(s, s);
    // Add(list, "v");
    Add(list, 90);
    
    Node *f = get_node(list, size(list) - 1);
    int fgata = *(int *)f->data;
    // char f_data = f->data;
    print_list(list);
    // printf("%c\n", f_data);

    Clear(list);

    print_list(list);

    return 0;
}