#include <stdio.h>
#include <string.h>
#include "Converters.hpp"

int tryToConvertStringtoInt(const char* InputString, int* resultValue) {
    char* endptr;
    *resultValue = strtol(InputString, &endptr, 10);
    if (endptr == InputString) {
        return 0;
    }
    return 1;
}

int tryToConvertStringtoDouble(const char* InputString, double* resultValue) {
    char* endptr;
    *resultValue = strtod(InputString, &endptr);
    if (endptr == InputString) {
        return 0;
    }
    return 1;
}
