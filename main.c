#include "LinkedList.h"

void func()
{
    int x = 0;
    return (double)x;
}

int main(int argc, char** argv)
{
    LinkedList* list = newLinkedList(INT);
    printf("%d", func());
    return 0;
}