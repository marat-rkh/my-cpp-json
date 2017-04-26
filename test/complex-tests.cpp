#include "gtest/gtest.h"
 
#include "mylib.h"

TEST (ComplexTests, Test1) { 
    EXPECT_EQ (1, one());
}

TEST (ComplexTests, Test2) { 
    EXPECT_EQ (1, one());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}