#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utility/InstructionDecoder.h>
#include <instructions/util/InstructionsRegistry.h>
#include <basicComponents/Memory.h>
#include <instructions/mov.h>
#include <basicComponents/Register.h>
#include <basicComponents/Cpu.h>

constexpr size_t DEFAULT_MEMORY_SIZE = 1024;

class InstructionDecoderTest : public testing::Test {
protected:
    const InstructionRegistry registry;
    InstructionDecoder decoder{registry};
    // TODO: mock Memory
    Memory memory{DEFAULT_MEMORY_SIZE};
    Cpu cpu{memory};
};

TEST_F(InstructionDecoderTest, testDecode) {

    Register32 eax{"EAX"};
    Register16 ds{"DS"};
    ds.set<Word>(0xFFFF);
    LogicalAddress baseAddress{ds, eax.get<Dword>()};
    memory.write<Byte>(baseAddress, 0x1);
    memory.write<Byte>(baseAddress + 1, 0xB0);

    const auto instruction = decoder.decode(baseAddress, cpu);
    const auto data = instruction->getInstructionData();

    const auto type = data.getProperty(OpPropertyKey::MovType);
    ASSERT_TRUE(std::holds_alternative<Word>(type));
    const auto movType = std::get<Word>(type);
    EXPECT_EQ(movType, MovType::val_to_reg);

    // TODO
    // const auto wBit = data.getProperty(OpPropertyKey::WBit);
    // const auto reg = data.getProperty(OpPropertyKey::Reg1);
    // const auto number = data.getProperty(OpPropertyKey::Reg1);
}
