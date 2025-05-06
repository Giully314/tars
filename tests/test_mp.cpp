#include <gtest/gtest.h>

import tars.mp;

using namespace tars;

TEST(TestMetaprogramming, BasicCounter) {
    auto a = unique_id();
    auto b = unique_id();
    auto c = unique_id();
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, a + 1);
    EXPECT_EQ(c, b + 1);
}