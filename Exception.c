#include "Exception.h"

#ifdef _WIN32
void printStackTrace()
{
    void *stack[100];
    unsigned short frames;
    SYMBOL_INFO *symbol;
    HANDLE process;

    process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    frames = CaptureStackBackTrace(0, 100, stack, NULL);
    symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    printf("Stack trace:\n");
    for (unsigned short i = 0; i < frames; i++)
    {
        SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
        printf("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
    }

    free(symbol);
}
#else
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
#endif
