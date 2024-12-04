#include "LinkedList.h"

int main()
{
    LinkedList* list = newLinkedList(char *);
    int x = 2, t = 2;

    Add(list, "ciao");
    Add(list, "sec");
    Add(list, "uil");

    char * f = GetLast(list);

    printf("%s\n", f);
    printf("%s\n", (char *)GetHead(list));

    free(list);

    return 0;
}