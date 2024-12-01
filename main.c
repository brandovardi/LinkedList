#include "LinkedList.h"

int main(int argc, char** argv)
{
    LinkedList* list = newLinkedList(STRING);
    char* str = "ciao";
    char* str1 = "ciao1";
    char* str2 = "ciao2";
    char* str3 = "ciao3";
    char* str4 = "ciao4";
    
    Add(list, str);
    Add(list, str1);
    Add(list, str2);
    Add(list, str3);
    Add(list, str4);
    
    PrintList(list);
    printf("Size: %d\n", SizeOf(list));

    RemoveAt(list,3);
    PrintList(list);
    printf("Size: %d\n", SizeOf(list));

    return 0;
}