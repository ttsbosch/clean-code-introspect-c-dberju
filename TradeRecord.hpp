#ifndef TRADERECORD_HPP
#define TRADERECORD_HPP
typedef struct {
    char SourceCurrency[256]; 
    char DestibationCurrency[256];
    float Lots;
    double Price;
} TradeRecord;
#endif

