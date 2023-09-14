#include <gtest/gtest.h>

#include <basicComponents/Flags.h>

TEST(StatusTest, testStatus){
    Flags efl;
    efl.CF.set(true);
    EXPECT_TRUE(efl.CF.get());
}
