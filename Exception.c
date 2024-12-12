#include "Exception.h"

void printStackTrace()
{
    size_t max_frames = 30; // Numero massimo di frame desiderati
    void **array = malloc(max_frames * sizeof(void *));
    if (!array)
    {
        fprintf(stderr, "Error: malloc failed.\n");
        return;
    }

    size_t size = backtrace(array, max_frames);
    char **strings = backtrace_symbols(array, size);

    printf("Stack trace:\n");
    for (size_t i = 0; i < size; printf("%s\n", *(strings + i)), i++)
        ;

    free(strings);
    free(array);
}
