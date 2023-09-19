#include <gtest/gtest.h>
#include <filesystem>

#include <basicComponents/Memory.h>

static constexpr auto testMemorySize = 1024;

class TestableMemory : public Memory {
public:
    TestableMemory(const std::string& filename) : Memory(filename, testMemorySize){}

    size_t size(){
        return bytes.size();
    }
};

TEST(MemoryTest, testWriteDword){
    Memory memory(testMemorySize);
    memory.write<Dword>(0x0, 0xB16B00B5);
    EXPECT_EQ(memory.read<Byte>(0x0), 0xB5);
    EXPECT_EQ(memory.read<Byte>(0x1), 0x00);
    EXPECT_EQ(memory.read<Byte>(0x2), 0x6B);
    EXPECT_EQ(memory.read<Byte>(0x3), 0xB1);
}

TEST(MemoryTest, testWriteWord){
    Memory memory(testMemorySize);
    memory.write<Word>(0x1, 0xDEAD);
    EXPECT_EQ(memory.read<Byte>(0x1), 0xAD);
    EXPECT_EQ(memory.read<Byte>(0x2), 0xDE);
}

TEST(MemoryTest, testWriteByte){
    Memory memory(testMemorySize);
    memory.write<Byte>(0x3, 0xCC);
    EXPECT_EQ(memory.read<Byte>(0x3), 0xCC);
}

TEST(MemoryTest, testRead){
    Memory memory(testMemorySize);
    memory.write<Dword>(0x0, 0x00DEFEC8);
    EXPECT_EQ(memory.read<Word>(0x0), 0xFEC8);
    EXPECT_EQ(memory.read<Dword>(0x0), 0x00DEFEC8);
    EXPECT_EQ(memory.read<Dword>(testMemorySize), 0x00DEFEC8);
}

TEST(MemoryTest, testOpenFile){
    TestableMemory memory("../../test/data/example_hex_file");
    ASSERT_EQ(memory.size(), testMemorySize);
    EXPECT_EQ(memory.read<Byte>(0x0), 'a');
    EXPECT_EQ(memory.read<Byte>(0x1), 'b');
    EXPECT_EQ(memory.read<Byte>(0x2), 'c');
    EXPECT_EQ(memory.read<Byte>(0x3), 'd');
    EXPECT_EQ(memory.read<Byte>(0x4), 'e');
    EXPECT_EQ(memory.read<Byte>(0x5), 'f');
}
