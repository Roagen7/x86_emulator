#pragma once

#include <util/InstructionIfc.h>
#include <basicComponents/Memory.h>
#include <basicComponents/Cpu.h>
#include <util/register_code.h>

#include <iostream>


class Push : public InstructionIfc {
    using InstructionIfc::InstructionIfc;

    Dword toPush;
    std::string regMnemonic;

    std::string mnemonic() const override {
        return "PUSH " + regMnemonic;
    }
    void fetch() override {
        auto opcode = cpu.getMemoryConst().read<Byte>(getOpcodeAddress());
        auto reg = getRegisterCode(cpu, opcode & 0b111, true);
        regMnemonic = reg.getMnemonic();
        toPush = reg.get<Dword>();
    }
    uint32_t size() const override {
        return 1;
    }
    void callback() const override {
        std::cout << mnemonic() << std::endl;
        cpu.esp.set<Dword>(cpu.esp.get<Dword>() - sizeof(Dword));
        auto addr = LogicalAddress{cpu.ss, cpu.esp.get<Dword>()};
        cpu.getMemory().write<Dword>(addr, toPush);
    }
};

template<>
inline bool InstructionBuilder<Push>::isInstruction(Byte opcode){
    return (opcode >> 3) == 0b01010;
}
