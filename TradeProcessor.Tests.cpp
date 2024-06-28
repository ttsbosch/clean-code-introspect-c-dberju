#include "gtest/gtest.h"
#include "Converters.hpp"
#include "CsvToXmlTradeRecordConverter.hpp"

TEST(ConvertStringToIntTest, ValidInput) {
    int resultValue;
    const char* validInput = "123";
    ASSERT_EQ(tryToConvertStringtoInt(validInput, &resultValue), 1);
    ASSERT_EQ(resultValue, 123);
}

TEST(ConvertStringToIntTest, InvalidInput) {
    int resultValue;
    const char* invalidInput = "abc";
    ASSERT_EQ(tryToConvertStringtoInt(invalidInput, &resultValue), 0);
    // resultValue should remain unchanged if conversion fails
}

TEST(ConvertStringToIntTest, EmptyString) {
    int resultValue;
    const char* emptyInput = "";
    ASSERT_EQ(tryToConvertStringtoInt(emptyInput, &resultValue), 0);
    // resultValue should remain unchanged if conversion fails
}

TEST(ConvertStringToIntTest, LeadingWhitespace) {
    int resultValue;
    const char* inputWithWhitespace = "   456";
    ASSERT_EQ(tryToConvertStringtoInt(inputWithWhitespace, &resultValue), 1);
    ASSERT_EQ(resultValue, 456);
}

TEST(ConvertStringToIntTest, TrailingCharacters) {
    int resultValue;
    const char* inputWithTrailingChars = "789xyz";
    ASSERT_EQ(tryToConvertStringtoInt(inputWithTrailingChars, &resultValue), 1);
    ASSERT_EQ(resultValue, 789);
}

TEST(tryToConvertStringtoDoubleTest, ValidInput) {
    double resultValue;
    const char* validInput = "123.001";
    ASSERT_EQ(tryToConvertStringtoDouble(validInput, &resultValue), 1);
    ASSERT_EQ(resultValue, 123.001);
}

TEST(tryToConvertStringtoDoubleTest, InvalidInput) {
    double resultValue;
    const char* invalidInput = "abc";
    ASSERT_EQ(tryToConvertStringtoDouble(invalidInput, &resultValue), 0);
    // resultValue should remain unchanged if conversion fails
}

TEST(MapCsvLineDataToTradeDataTest, ValidCsvLines) {
    char* mockCsvData[NUMBER_OF_LINES_IN_CSV] = {
        "USD,199,1.2345",
        "GBP,111,105.67",
        "AUD,100,0.9876"
    };

    TradeDataInString* result = mapCsvLineDataToTradeData(mockCsvData);

    // Validate the first line
    EXPECT_STREQ(result[0].tradeCurrencies, "USD");
    EXPECT_STREQ(result[0].tradeAmount, "199");
    EXPECT_STREQ(result[0].tradePrice, "1.2345");

    // Validate the second line
    EXPECT_STREQ(result[1].tradeCurrencies, "GBP");
    EXPECT_STREQ(result[1].tradeAmount, "111");
    EXPECT_STREQ(result[1].tradePrice, "105.67");

    // Validate the third line
    EXPECT_STREQ(result[2].tradeCurrencies, "AUD");
    EXPECT_STREQ(result[2].tradeAmount, "100");
    EXPECT_STREQ(result[2].tradePrice, "0.9876");

    free(result);
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
