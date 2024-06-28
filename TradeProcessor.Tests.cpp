#include "gtest/gtest.h"

TEST(ConvertStringToIntTest, ValidInput) {
    int resultValue;
    const char* validInput = "123";
    ASSERT_EQ(tryToConvertStringtoInt(validInput, &resultValue), 1);
    ASSERT_EQ(resultValue, 123);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
