#include <gtest/gtest.h>

#include "../main/Register.h"

TEST(RegisterTest, testRegister){
    Register32 eax{"EAX"};
    eax.set<Dword>(0xFFDEFEC8);
    EXPECT_EQ(eax.get<Dword>(), 0xFFDEFEC8);
    eax.set<Word>(0xBEEF);
    EXPECT_EQ(eax.get<Dword>(), 0xFFDEBEEF);
    eax.set<Byte>(0xCC);
    EXPECT_EQ(eax.get<Dword>(), 0xFFDEBECC);
    eax.set<Byte,1>(0xDD);
    EXPECT_EQ(eax.get<Dword>(), 0xFFDEDDCC);
}