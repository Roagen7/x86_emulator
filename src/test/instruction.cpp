#include <gtest/gtest.h>

#include "../main/Memory.h"
#include "util/BinaryRunner.h"

static constexpr auto testMemorySize = 1024;

TEST(InstructionTest, addTest){
    BinaryRunner({
        0x0, 0x0, 0x0
    });
    
}