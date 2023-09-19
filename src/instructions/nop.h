#pragma once

#include <util/InstructionIfc.h>
#include <basicComponents/Memory.h>
#include <basicComponents/Cpu.h>
#include <util/register_code.h>

#include <iostream>


class Nop : public InstructionIfc {
    using InstructionIfc::InstructionIfc;

    std::string mnemonic() const override {
        return "NOP";
    }
    void fetch() override {
  
    }
    uint32_t size() const override {
        return 1;
    }
    void callback() const override {
        std::cout << mnemonic() << std::endl;
    }
};

template<>
inline bool InstructionBuilder<Nop>::isInstruction(Byte opcode){
    return opcode == 0x90;
}
