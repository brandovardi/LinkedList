#pragma once

// per gestire le eccezioni (stack trace)
// https://stackoverflow.com/questions/77005/how-to-generate-a-stacktrace-when-my-gcc-c-app-crashes
#ifdef _WIN32
#include <windows.h>
#include <DbgHelp.h>
#else
#include <execinfo.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef _EXCEPTION_H
#define _EXCEPTION_H

void printStackTrace();

#endif /* _EXCEPTION_H */
