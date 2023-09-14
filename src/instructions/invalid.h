#pragma once

#include <instructions/InstructionIfc.h>
#include <iostream>

class Invalid : public InstructionIfc {
    std::string mnemonic() const override {
        return "ERROR";
    }
    void fetch(Cpu& cpu) override {
        
    }
    uint32_t size() const override {
        return 0;
    }
    void callback(Cpu& cpu) const override {
        // TODO: invalid/unsupported opcode handling
        std::cout << "INVALID OPCODE" << std::endl;
    }
};
