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

TEST(BinaryRunnerTest ,testBinaryRunnerNoops){
    BinaryRunner runner("../../test/data/compiled/noops");
    auto eaxBefore = runner.cpu.eax.get<Dword>();
    runner.cpu.cs.set<Word>(0);
    runner.run(3);
    EXPECT_EQ(eaxBefore, runner.cpu.eax.get<Dword>());
    EXPECT_EQ(runner.memory.read<Byte>(0x0), 0x90);
    EXPECT_EQ(runner.memory.read<Byte>(0x0), 0x90);
    EXPECT_EQ(runner.memory.read<Byte>(0x0), 0x90);
}