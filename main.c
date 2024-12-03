#include "LinkedList.h"

int main(int argc, char** argv)
{
    LinkedList* list = newLinkedList("int");
    char* c = "CIAO\0";
    printf("%s\n", c);
    c = ToLower(c);
    printf("%s\n", c);
    
    free(list);

    return 0;
}