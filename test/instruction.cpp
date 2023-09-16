#include <gtest/gtest.h>

#include <basicComponents/Memory.h>
#include <instructions/util/register_code.h>
#include <util/BinaryRunner.h>
#include <instructions/push.h>

static constexpr auto testMemorySize = 1048576;

TEST(InstructionTest, testAdd){
    BinaryRunner({
        0x0, 0x0, 0x0
    });
    
}

TEST(InstructionTest, testRegisterCode){
    Memory memory(testMemorySize);
    Cpu cpu(memory);
    EXPECT_EQ(&getRegisterCode(cpu, 0b000, 0), &cpu.eax);
    EXPECT_EQ(&getRegisterCode(cpu, 0b001, 0), &cpu.ecx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b010, 0), &cpu.edx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b011, 0), &cpu.ebx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b100, 0), &cpu.eax);
    EXPECT_EQ(&getRegisterCode(cpu, 0b101, 0), &cpu.ecx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b110, 0), &cpu.edx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b111, 0), &cpu.ebx);

    EXPECT_EQ(&getRegisterCode(cpu, 0b000, 1), &cpu.eax);
    EXPECT_EQ(&getRegisterCode(cpu, 0b001, 1), &cpu.ecx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b010, 1), &cpu.edx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b011, 1), &cpu.ebx);
    EXPECT_EQ(&getRegisterCode(cpu, 0b100, 1), &cpu.esp);
    EXPECT_EQ(&getRegisterCode(cpu, 0b101, 1), &cpu.ebp);
    EXPECT_EQ(&getRegisterCode(cpu, 0b110, 1), &cpu.esi);
    EXPECT_EQ(&getRegisterCode(cpu, 0b111, 1), &cpu.edi);
}

TEST(InstructionTest, testPush){

    InstructionBuilder<Push> ib;
    
    EXPECT_TRUE(ib.isInstruction(0x50));
    EXPECT_FALSE(ib.isInstruction(0x58));

    BinaryRunner runner({
        0x50,    // push eax
        0x51,    // push ecx
        0x52,    // push edx
        0x53,    // push ebx
        0x55,    // push ebp
        0x56,    // push esi
        0x57,    // push edi
    });
    runner.cpu.cs.set<Word>(0x0);
    runner.cpu.eax.set<Dword>(0xDEADBEEF);
    runner.cpu.ecx.set<Dword>(0xB16B00B5);
    runner.cpu.edx.set<Dword>(0x00DEFEC8);
    runner.cpu.ebx.set<Dword>(0x0B00B135);
    runner.cpu.ebp.set<Dword>(0xBEEFBABE);
    runner.cpu.esi.set<Dword>(0xBA5EBA11);
    runner.cpu.edi.set<Dword>(0x1337BEEF);
    
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFFC);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFEC), 0xDEADBEEF);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFF8);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFE8), 0xB16B00B5);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFF4);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFE4), 0x00DEFEC8);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFF0);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFE0), 0x0B00B135);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFEC);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFDC), 0xBEEFBABE);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFE8);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFD8), 0xBA5EBA11);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFE4);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFD4), 0x1337BEEF);
    
}

TEST(InstructionTest, testPushEsp){
   BinaryRunner runner({
        0x54     // push esp
    });
    runner.cpu.cs.set<Word>(0x0);
    runner.run(1);
    EXPECT_EQ(runner.cpu.esp.get<Dword>(), 0xFFFFFFFC);
    EXPECT_EQ(runner.memory.read<Dword>(0xFFFEC), 0x0);
}
