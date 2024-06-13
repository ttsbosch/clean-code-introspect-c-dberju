#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "StringHelper.hpp"

char** SplitString(const char* inputString, char delimiter) {
    int delimiterCount = 0;
    const char* ptr = inputString;
    while (*ptr != '\0') {
        if (*ptr++ == delimiter) {
            delimiterCount++;
        }
    }

    char** tokenSet = (char**)malloc(sizeof(char*) * (delimiterCount + 2));
    int tokenSetIterator = 0;
    ptr = inputString;
    char* token = (char*)malloc(strlen(inputString) + 1);
    int tokenIterator = 0;
    while (*ptr != '\0') {
        if (*ptr == delimiter) {
            token[tokenIterator] = '\0';
            tokenSet[tokenSetIterator++] = strdup(token);
            tokenIterator = 0;
        } else {
            token[tokenIterator++] = *ptr;
        }
        ptr++;
    }
    token[tokenIterator] = '\0';
    tokenSet[tokenSetIterator++] = strdup(token);
    tokenSet[tokenSetIterator] = NULL;
    free(token);
    return tokenSet;
}
