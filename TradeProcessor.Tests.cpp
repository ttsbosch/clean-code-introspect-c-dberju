#include "gtest/gtest.h"
#include "Converters.hpp"
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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
