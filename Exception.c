#include "Exception.h"

#ifdef _WIN32

void printStackTrace()
{
    const size_t max_frames = 30; // Maximum number of frames
    void *stack[max_frames];
    HANDLE process = GetCurrentProcess();

    // Initialize DbgHelp library
    SymInitialize(process, NULL, true);

    // Capture stack trace
    USHORT frames = CaptureStackBackTrace(0, max_frames, stack, NULL);

    // Allocate symbol info structure
    SYMBOL_INFO *symbol = (SYMBOL_INFO *)malloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char));
    (symbol == NULL) ? (fprintf(stderr, "Error: malloc failed.\n"), exit(EXIT_FAILURE)) : 0;

    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    // Print stack trace
    printf("Stack trace:\n");
    for (USHORT i = 0; i < frames; i++)
        (SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol)) ? printf("[%i] %s - 0x%0llX\n", i, symbol->Name, symbol->Address) : printf("[%i] ??? - 0x%0llX\n", i, (DWORD64)(stack[i]));

    // Cleanup
    free(symbol);
    SymCleanup(process);
}

#elif __linux__

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
