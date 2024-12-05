#include "LinkedList.h"

int main()
{
    LinkedList *list = newLinkedList(char *);
    int x = 2, t = 2;

    char * s = "sudo";
    Add(list, s);
    Add(list, "ciao");
    Add(list, "ee");
    // Add(list, "asidojas");

    __builtin_va_list *ca;
    

    char *f = GetLast(list);

    printf("%s\n", f);
    // printf("%s\n", GetHead(list));

    free(list);

    return 0;
}