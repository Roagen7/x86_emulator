#include <gtest/gtest.h>

#include <basicComponents/Fpu.h>

TEST(FpuTest, testStAccess){
    Fpu fpu;
    RegisterFpu sth;
    sth.set<double>(1.0);
    fpu.push(sth);
    EXPECT_DOUBLE_EQ(fpu.st(0).get<double>(), 1.0);
    sth.set<float>(2.f);
    fpu.push(sth);
    EXPECT_DOUBLE_EQ(fpu.st(0).get<double>(), 2.0);
    EXPECT_DOUBLE_EQ(fpu.st(1).get<double>(), 1.0);
    sth.set<double>(3.0);
    fpu.push(sth);
    EXPECT_DOUBLE_EQ(fpu.st(0).get<double>(), 3.0);
    EXPECT_DOUBLE_EQ(fpu.st(1).get<double>(), 2.0);
    EXPECT_DOUBLE_EQ(fpu.st(2).get<double>(), 1.0);
}

TEST(FpuTest, testFpuStackOverflow){
    Fpu fpu;
    for(size_t i = 0u ; i < 8; i++){
        EXPECT_TRUE(fpu.push(RegisterFpu()));
    }
    EXPECT_FALSE(fpu.push(RegisterFpu()));
}

