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

TEST(ValidateAndPopulateTradeDataTest, ValidData) {
    TradeDataInString mockTradeData[3] = {
        {"USDEUR", "100", "1.2345"}, // Valid data
        {"GBPJPY", "200", "105.67"}, // Valid data
        {"AUDCAD", "300", "0.9876"}  // Valid data
    };

    TradeRecord* result = validateAndPopulateTradeData(mockTradeData);

    // Validate the first trade record
    EXPECT_STREQ(result[0].SourceCurrency, "USD");
    EXPECT_STREQ(result[0].DestibationCurrency, "EUR");
    EXPECT_FLOAT_EQ(result[0].Lots, 100.0);
    EXPECT_DOUBLE_EQ(result[0].Price, 1.2345);

    // Validate the second trade record
    EXPECT_STREQ(result[1].SourceCurrency, "GBP");
    EXPECT_STREQ(result[1].DestibationCurrency, "JPY");
    EXPECT_FLOAT_EQ(result[1].Lots, 200.0);
    EXPECT_DOUBLE_EQ(result[1].Price, 105.67);

    // Validate the third trade record
    EXPECT_STREQ(result[2].SourceCurrency, "AUD");
    EXPECT_STREQ(result[2].DestibationCurrency, "CAD");
    EXPECT_FLOAT_EQ(result[2].Lots, 300.0);
    EXPECT_DOUBLE_EQ(result[2].Price, 0.9876);

    free(result);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
