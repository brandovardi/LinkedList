#include "LinkedList.h"

int main()
{
    LinkedList *list = newLinkedList(int);

    char * s = "45";

    // InsertAt(list, 98, 0);

    Add(list, 1);
    Add(list, 2);
    Add(list, s);
    Add(list, "v");
    
    Node *f = get_node(list, size(list) - 1);
    // char f_data = f->data;
    print_list(list);
    // printf("%c\n", f_data);

    Clear(list);

    print_list(list);

    return 0;
}