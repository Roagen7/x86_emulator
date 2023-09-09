#pragma once

#include "../IInstruction.h"

class Add : public IInstruction {
    std::string mnemonic() const override {
        return "ADD";
    }
    void callback(Cpu& cpu) const override {

    }
};

template<>
bool InstructionBuilder<Add>::isInstruction(const Memory& memory, const Cpu& cpu){
    return true;
}
