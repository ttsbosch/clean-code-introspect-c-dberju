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

class CsvReadTest : public ::testing::Test {
protected:
    // Helper function to create a temporary file with given content
    void createTempFile(const char* filename, const char* content) {
        FILE *file = fopen(filename, "w");
        if (file) {
            fputs(content, file);
            fclose(file);
        }
    }

    // Helper function to delete the temporary file
    void deleteTempFile(const char* filename) {
        remove(filename);
    }
};

TEST_F(CsvReadTest, ReadValidCsvFile) {
    const char* filename = "test_valid.csv";
    const char* content = "INRDOL,500,1000\nDOLINR,600,2000\nINRLAR,200,3000\n";
    createTempFile(filename, content);

    FILE *file = fopen(filename, "r");
    ASSERT_NE(file, nullptr);

    char **lines = ReadTradeDataFromCsv(file);

    fclose(file);
    deleteTempFile(filename);

    ASSERT_NE(lines, nullptr);

    // Check if the lines are read correctly
    EXPECT_STREQ(lines[0], "INRDOL,500,1000\n");
    EXPECT_STREQ(lines[1], "DOLINR,600,2000\n");
    EXPECT_STREQ(lines[2], "INRLAR,200,3000\n");

    // Free allocated memory
    for (int i = 0; lines[i] != NULL; ++i) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
