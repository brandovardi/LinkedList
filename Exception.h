#pragma once

// per gestire le eccezioni (stack trace)
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _EXCEPTION_H
#define _EXCEPTION_H

void printStackTrace();

#endif /* _EXCEPTION_H */
