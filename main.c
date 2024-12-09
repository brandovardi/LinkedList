#include "LinkedList.h"

typedef struct Macchina Macchina;

int main()
{
    LinkedList *list = newLinkedList(int);

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