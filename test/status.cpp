#include <gtest/gtest.h>

#include <basicComponents/Flags.h>
#include <utility/Widths.h>

TEST(StatusTest, testStatus){
    Flags efl;
    efl.CF.set(true);
    EXPECT_TRUE(efl.CF.get());
}

TEST(StatusTest, testZero){
    Flags efl;
    efl.setAddFlags<Byte>(0,  0);
    EXPECT_TRUE(efl.ZF.get());
    efl.setAddFlags<Byte>(0,  1);
    EXPECT_FALSE(efl.ZF.get());
}

TEST(StatusTest, testSign){
    Flags efl;
    efl.setAddFlags<Byte>(0, 0x80);
    EXPECT_TRUE(efl.SF.get());
    efl.setAddFlags<Byte>(0, 0);
    EXPECT_FALSE(efl.SF.get());
    efl.setAddFlags<Word>(0, 0x8000);
    EXPECT_TRUE(efl.SF.get());
    efl.setAddFlags<Word>(0, 0);
    EXPECT_FALSE(efl.SF.get());
    efl.setAddFlags<Dword>(0, 0x80000000);
    EXPECT_TRUE(efl.SF.get());
    efl.setAddFlags<Dword>(0, 0);
    EXPECT_FALSE(efl.SF.get());
}

TEST(StatusTest, testParity){
    Flags efl;
    efl.setAddFlags<Byte>(0, 0);
    EXPECT_TRUE(efl.PF.get());
    efl.setAddFlags<Byte>(0, 0b11010101);
    EXPECT_FALSE(efl.PF.get());
    efl.setAddFlags<Word>(0, 0b111010101);
    EXPECT_FALSE(efl.PF.get());
    efl.setAddFlags<Word>(0, 0b111011101);
    EXPECT_TRUE(efl.PF.get());
    efl.setAddFlags<Word>(0, 0b11011101);
    EXPECT_TRUE(efl.PF.get());
}

TEST(StatusTest, testOverflow){
    Flags efl;
    efl.setAddFlags<Byte>(0b01000000, 0b01000000);
    EXPECT_TRUE(efl.OF.get());
    efl.setAddFlags<Byte>(0, 0, 0);
    EXPECT_FALSE(efl.OF.get());
    efl.setAddFlags<Word>(0x8000, 0x8000);
    EXPECT_TRUE(efl.OF.get());
    efl.setAddFlags<Word>(0x80, 0x8000);
    EXPECT_FALSE(efl.OF.get());
}

TEST(StatusTest, testCarry){
    Flags efl;
    efl.setAddFlags<Byte>(0b10000000, 0b10000000);
    EXPECT_TRUE(efl.CF.get());
    efl.setAddFlags<Byte>(0x80, 0);
    EXPECT_FALSE(efl.CF.get());
    efl.setAddFlags<Dword>(0x80000000, 0x80000000);
    EXPECT_TRUE(efl.CF.get());
}

TEST(StatusTest, testAuxCarry){
    Flags efl;
    efl.setAddFlags<Byte>(0b1000, 0b1000);
    EXPECT_TRUE(efl.AF.get());
    efl.setAddFlags<Byte>(0b0000, 0b1000);
    EXPECT_FALSE(efl.AF.get());
    efl.setAddFlags<Byte>(0b10000, 0b1000);
    EXPECT_FALSE(efl.AF.get());
    efl.setAddFlags<Byte>(0b0000, 0b1000);
    EXPECT_FALSE(efl.AF.get());   
    efl.setAddFlags<Byte>(0b11000, 0b1000);
    EXPECT_TRUE(efl.AF.get());
}

TEST(StatusTest, testOmitCarry){
  Flags efl;
    efl.setAddFlags<Byte>(0b10000000, 0b10000000, true);
    EXPECT_FALSE(efl.CF.get());
    efl.setAddFlags<Byte>(0x80, 0);
    EXPECT_FALSE(efl.CF.get());
    efl.setAddFlags<Dword>(0x80000000, 0x80000000, true);
    EXPECT_FALSE(efl.CF.get());
}

