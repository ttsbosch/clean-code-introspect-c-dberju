#ifndef CSVTOXMLTRADERECORDCONVERTER_HPP
#define CSVTOXMLTRADERECORDCONVERTER_HPP

#include <stdio.h>
#include "TradeRecord.hpp"
typedef struct 
{
    char tradeCurrencies[100];
    char tradeAmount[100];
    char tradePrice[100];
}TradeDataInString;

char **ReadTradeDataFromCsv(FILE *filePointer);
TradeDataInString* mapCsvLineDataToTradeData(char **lineInFile);
TradeRecord* validateAndPopulateTradeData(TradeDataInString *tradeData);
FILE * writeTradeDataToXml(TradeRecord *tradeRecord);


#endif
