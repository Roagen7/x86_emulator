#include <gtest/gtest.h>

#include <basicComponents/Memory.h>
#include <util/BinaryRunner.h>


TEST(BinaryRunnerTest, testBinaryRunner){
    BinaryRunner runner({
        0x0, 0x0, 0x0
    });
    static constexpr auto numTicks = 3u;
    runner.run(numTicks);
    ASSERT_EQ(runner.cpu.getTickCounter(), numTicks);
}
