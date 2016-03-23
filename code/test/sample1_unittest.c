#include <limits.h>
#include "../src/sample1.h"
#include "gtest/gtest.h"

// Test sum
TEST(FactorialTest, Test_A) {
  EXPECT_EQ(1, my_sum(0,1));
}

TEST(FactorialTest, Test_B) {
  EXPECT_EQ(5, my_sum(2,3));
  EXPECT_EQ(12, my_sum(10,2));
}
