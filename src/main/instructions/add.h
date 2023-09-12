#pragma once

#include "../IInstruction.h"
#include <iostream>

class Add : public IInstruction {
    std::string mnemonic() const override {
        return "ADD";
    }
    void fetch(const Cpu& cpu) override {
        
    }
    void callback(Cpu& cpu) const override {
        std::cout << mnemonic() << std::endl;
    }
};

template<>
inline bool InstructionBuilder<Add>::isInstruction(const Memory& memory, const Cpu& cpu){
    return true;
}
