#include "LinkedList.h"
#include <X11/Xlib.h>

int main()
{
    LinkedList *list = newLinkedList(char);
    int x = 2, t = 2;

    char s = 'a';

    Add(list, 'c');
    Add(list, 'b');
    Add(list, s);
    
    Node *f = GetLast(list);
    char f_data = (char)f->data;
    PrintList(list);
    printf("%s\n", f_data);

    free(list);

    return 0;
}