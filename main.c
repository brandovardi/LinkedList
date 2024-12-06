#include "LinkedList.h"

int main()
{
    LinkedList *list = newLinkedList(char);

    char s = 'a';

    InsertAt(list, 'j', 0);

    Add(list, 'c');
    Add(list, 'b');
    Add(list, s);
    
    Node *f = get_last_node(list);
    // char f_data = f->data;
    print_list(list);
    // printf("%c\n", f_data);

    Clear(list);

    print_list(list);

    return 0;
}