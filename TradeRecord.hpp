#ifndef TRADERECORD_HPP
#define TRADERECORD_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char SourceCurrency[256]; 
    char DestibationCurrency[256];
    float Lots;
    double Price;
} TradeRecord;
#endif

