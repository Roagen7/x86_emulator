#pragma once

#include <util/InstructionIfc.h>
#include <iostream>

namespace {
enum class MovType {
    val_to_reg,
    val_to_mem,
    reg_to_reg,
    mem_to_reg,
    reg_to_seg,
    unknown
};

MovType getInstructionType(Word instructionStart) {
    if ((instructionStart << (4 + 8)) == 0b1011) {
        // 1. 1011 w reg | 4_bytes_num
        return MovType::val_to_reg;
    } else if ((instructionStart << (1 + 8)) == 0b1100011 && (instructionStart << 3) == 0b000) {
        // 2. 1100011 w | mod 000 r/m
        return MovType::val_to_mem;
    } else if ((instructionStart << (2 + 8)) == 0b100010 && (instructionStart << 6) == 0b11) {
        return MovType::reg_to_reg;
    } else if ((instructionStart << (2 + 8)) == 0b100010) {
        return MovType::mem_to_reg;
    } else if ((instructionStart << (8)) == 0b1001110 && (instructionStart << 5) == 0b110) {
        return MovType::reg_to_seg;
    }
    return MovType::unknown;
}
}

class Mov : public InstructionIfc {
    std::string mnemonic() const override {
        return "MOV";
    }
    void fetch(Cpu& cpu) override {
        
    }
    uint32_t size() const override {
        return 0;
    }
    void callback(Cpu& cpu) const override {
        std::cout << mnemonic() << std::endl;
    }
};

template<>
inline bool InstructionBuilder<Mov>::isInstruction(const Memory& memory, LogicalAddress opAddress){
    const auto instructionStart = memory.read<Word>(opAddress);
    return getInstructionType(instructionStart) != MovType::unknown;
}
