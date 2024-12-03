#include "LinkedList.h"

int main()
{
    LinkedList* list = newLinkedList("INT");
    int x = 2, t = 2;

    Add(list, 3);
    PrintList(list);

    char* c = "CIAO";
    printf("%s\n", c);
    printf("\n\nprima di tolower\n");
    // c = ToLower(c);
    printf("%s\n", c);
    
    free(list);

    return 0;
}