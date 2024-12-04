#include "LinkedList.h"

int main()
{
    LinkedList* list = newLinkedList(int);
    int x = 2, t = 2;

    InsertAt(list, 3, 0);
    
    free(list);

    return 0;
}