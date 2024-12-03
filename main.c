#include "LinkedList.h"

int main(int argc, char** argv)
{
    LinkedList* list = newLinkedList("int");
    char* c = "CIAO\0";
    printf("%s", c);
    c = tolower_str(c);
    printf("%s", c);
    
    free(list);

    return 0;
}