#pragma once

#include <util/InstructionIfc.h>
#include <iostream>

class Sub : public InstructionIfc {
    using InstructionIfc::InstructionIfc;
    std::string mnemonic() const override {
        return "SUB";
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
inline InstructionData InstructionBuilder<Sub>::parseData(const Memory& memory, LogicalAddress opAddress) {
    // TODO
    return {};
}

template<>
inline bool InstructionBuilder<Sub>::isInstruction(const Memory& memory, LogicalAddress opAddress){
    return false;
}
