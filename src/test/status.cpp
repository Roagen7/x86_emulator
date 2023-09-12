#include "gtest/gtest.h"
#include "../main/Flags.h"

TEST(status, testStatus){
    Flags efl;
    efl.CF.set(true);
    EXPECT_TRUE(efl.CF.get());
}