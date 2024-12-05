#include "LinkedList.h"
#include <X11/Xlib.h>

int main()
{
    LinkedList *list = newLinkedList(char *);
    int x = 2, t = 2;

    if (NULL == NULL)
    {
        printf("NULL\n");
    }
    
    char *p = GetHead(list);

    char * s = "sudo";
    {
        __typeof__("ciao") _tmp = ("ciao");
        add(list, &_tmp, ((list == ((void *)0)) ? 0 : ((!GetHead(list)) ? (SetHead(list, &_tmp, __typeof__(_tmp)) ? 1 : 0) : (SameType(GetHead(list), _tmp) ? 1 : 0))));
    }
    Add(list, "ciao");
    Add(list, s);
    // Add(list, "ee");
    // Add(list, "asidojas");
    
    char *f = GetLast(list);

    printf("%s\n", f);
    // printf("%s\n", GetHead(list));

    free(list);

    return 0;
}