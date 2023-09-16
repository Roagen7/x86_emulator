#pragma once

#include <util/InstructionIfc.h>
#include <iostream>

enum MovType {
    val_to_reg = 0,
    val_to_mem,
    reg_to_reg,
    mem_to_reg,
    reg_to_seg,
    unknown
};

namespace {
MovType getInstructionType(Word instructionStart) {
    if ((instructionStart >> (4 + 8)) == 0b1011) {
        // 1011 w reg | 4_bytes_num
        return MovType::val_to_reg;
    } else if ((instructionStart >> (1 + 8)) == 0b1100011 && (instructionStart >> 3) == 0b000) {
        // 1100011 w | mod 000 r/m
        return MovType::val_to_mem;
    } else if ((instructionStart >> (2 + 8)) == 0b100010 && (instructionStart >> 6) == 0b11) {
        // 100010 d w | 11 reg r/m
        return MovType::reg_to_reg;
    } else if ((instructionStart >> (2 + 8)) == 0b100010) {
        // 100010 d w | mod reg r/m
        return MovType::mem_to_reg;
    } else if ((instructionStart >> (8)) == 0b1001110 && (instructionStart >> 5) == 0b110) {
        // 10001110 | 110 rsgm reg
        return MovType::reg_to_seg;
    }
    return MovType::unknown;
}
}

class Mov : public InstructionIfc {
    using InstructionIfc::InstructionIfc;

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
inline InstructionData InstructionBuilder<Mov>::parseData(const Memory& memory, LogicalAddress opAddress) {
    const auto instructionStart = memory.read<Word>(opAddress);
    const auto type = getInstructionType(instructionStart);
    InstructionData data;
    data.setProperty<Word>(OpPropertyKey::MovType, type);
    // TODO
    return data;
}

template<>
inline bool InstructionBuilder<Mov>::isInstruction(const Memory& memory, LogicalAddress opAddress){
    const auto instructionStart = memory.read<Word>(opAddress);
    return getInstructionType(instructionStart) != MovType::unknown;
}
