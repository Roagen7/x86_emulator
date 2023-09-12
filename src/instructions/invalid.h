#pragma once

#include "../IInstruction.h"
#include <iostream>

class Invalid : public IInstruction {
    std::string mnemonic() const override {
        return "ERROR";
    }
    void fetch(const Cpu& cpu) override {
        
    }
    void callback(Cpu& cpu) const override {
        // TODO: invalid/unsupported opcode handling
        std::cout << "INVALID OPCODE" << std::endl;
    }
};