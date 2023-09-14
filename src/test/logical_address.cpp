#include <gtest/gtest.h>

#include "../main/Register.h"
#include "../main/Memory.h"

static constexpr auto testMemorySize = 1024;



TEST(LogicalAddressTest, testLogicalAddress){
    Register32 eax{"EAX"};
    Register16 ds{"DS"};
    ds.set<Word>(0xFFFF);
    Address l1 = LogicalAddress{ds, eax.get<Dword>()};
    EXPECT_EQ(l1, 0xFFFF0);
    eax.set<Dword>(0xB5);
    ds.set<Word>(0xB000);
    Address l2 = LogicalAddress{ds, eax.get<Dword>()};
    EXPECT_EQ(l2, 0xB00B5);
}

