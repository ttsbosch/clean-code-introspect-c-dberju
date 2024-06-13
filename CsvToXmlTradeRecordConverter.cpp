#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

void convertDataFromCsvToXml(FILE* stream) {
    char line[1024];
    TradeRecord tradeRecord[1024];
    int lineCount = 0;
    int objectCount = 0;

    while (fgets(line, sizeof(line), stream)) {
        char* fields[3];
        int fieldCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        if (fieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, fieldCount);
            continue;
        }

        if (strlen(fields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, fields[0]);
            continue;
        }

        int tradeAmount;
        if (!tryToConvertStringtoInt(fields[1], &tradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, fields[1]);
        }

        double tradePrice;
        if (!tryToConvertStringtoDouble(fields[2], &tradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, fields[2]);
        }

        strncpy(tradeRecord[objectCount].SourceCurrency, fields[0], 3);
        strncpy(tradeRecord[objectCount].DestibationCurrency, fields[0] + 3, 3);
        tradeRecord[objectCount].Lots = tradeAmount / LotSize;
        tradeRecord[objectCount].Price = tradePrice;
        objectCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int index = 0; index < objectCount; index++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", tradeRecord[index].SourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", tradeRecord[index].DestibationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", tradeRecord[index].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", tradeRecord[index].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", objectCount);
}
