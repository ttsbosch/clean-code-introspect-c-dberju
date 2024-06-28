#include "gtest/gtest.h"
Test(, tryToConvertStringtoInt)
{
  int result_val;
  char *string = "Bosch";
  ASSERT_EQ(1,tryToConvertStringtoInt(string,result_val));
}
