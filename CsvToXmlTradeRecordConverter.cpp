#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define INITIAL_CAPACITY 10
#define NUMBER_OF_LINES_IN_CSV 3
#include "Converters.hpp"
#include "TradeRecord.hpp"

typedef struct 
{
    char tradeCurrencies[100];
    char tradeAmount[100];
    char tradePrice[100];
}TradeDataInString;

char **ReadTradeDataFromCsv(FILE *filePointer)
{
    char **lines = NULL;
    char line[1024];
    int capacity = INITIAL_CAPACITY;
    int count = 0;

    // Allocate initial memory for lines array
    lines = (char **)malloc(capacity * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    while (fgets(line, sizeof(line), filePointer)) {
        // Allocate memory for the line
        lines[count] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        memcpy(lines[count] , line, strlen(line));
        //printf("%s\n",lines[count]);
        count++;
    }

    return lines;
}

TradeDataInString* mapCsvLineDataToTradeData(char **lineInFile)
{
    TradeDataInString *tradeData;
    tradeData = (TradeDataInString*) malloc ( NUMBER_OF_LINES_IN_CSV * sizeof(tradeData));
    char* fields[3];
    int fieldCount = 0;

    int index = 0;
    for (index = 0; index < NUMBER_OF_LINES_IN_CSV ; index++)
    {
        fieldCount = 0;
        char* token = strtok( lineInFile[index] , ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        memcpy(tradeData[index].tradeCurrencies, fields[0] , strlen(fields[0]));
        memcpy(tradeData[index].tradeAmount, fields[1] , strlen(fields[0]));
        memcpy(tradeData[index].tradePrice, fields[2] , strlen(fields[0]));
    }

    return tradeData;
} 

TradeRecord* validateAndPopulateTradeData(TradeDataInString *tradeData)
{
    int LotSize = 1;
    TradeRecord *tradeRecord;
    tradeRecord = (TradeRecord*) malloc ( NUMBER_OF_LINES_IN_CSV * sizeof(TradeRecord));

    for(int index = 0 ; index < NUMBER_OF_LINES_IN_CSV ; index++ )
    {
        //if (strlen(tradeData[index].tradeCurrencies) != 6) {
        //    fprintf(stderr, "WARN: Trade currencies malformed: '%s'\n", tradeData[index].tradeCurrencies);
         //   continue;
        //}

        int tradeAmount;
        tryToConvertStringtoInt(tradeData[index].tradeAmount, &tradeAmount);
        //if (!tryToConvertStringtoInt(tradeData[index].tradeAmount, &tradeAmount)) {
        //    fprintf(stderr, "WARN: Trade amount  not a valid integer: '%s'\n", tradeData[index].tradeAmount);
        //    continue;
        //}

        double tradePrice;
        tryToConvertStringtoDouble(tradeData[index].tradePrice, &tradePrice);
        //if (!tryToConvertStringtoDouble(tradeData[index].tradePrice, &tradePrice)) {
         //   fprintf(stderr, "WARN: Trade price  not a valid decimal: '%s'\n", tradeData[index].tradePrice);
        //}
    
        strncpy(tradeRecord[index].SourceCurrency, tradeData[index].tradeCurrencies, 3);
        strncpy(tradeRecord[index].DestibationCurrency, tradeData[index].tradeCurrencies + 3, 3);
        tradeRecord[index].Lots = tradeAmount / LotSize;
        tradeRecord[index].Price = tradePrice;
    }
    return tradeRecord;
}

FILE * writeTradeDataToXml(TradeRecord *tradeRecord)
{
    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int index = 0; index < NUMBER_OF_LINES_IN_CSV; index++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", tradeRecord[index].SourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", tradeRecord[index].DestibationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", tradeRecord[index].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", tradeRecord[index].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    return outFile;
}

