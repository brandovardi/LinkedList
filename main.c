#include "LinkedList.h"

int main()
{
    LinkedList* list = newLinkedList("INT");
    int x = 2, t = 2;

    Add(list, 3);
    PrintList(list);
    
    free(list);
    
    return 0;
}