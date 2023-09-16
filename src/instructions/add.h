#pragma once

#include <util/InstructionIfc.h>
#include <iostream>

class Add : public InstructionIfc {
    using InstructionIfc::InstructionIfc;
    std::string mnemonic() const override {
        return "ADD";
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
inline InstructionData InstructionBuilder<Add>::parseData(const Memory& memory, LogicalAddress opAddress) {
    // TODO
    return {};
}

template<>
inline bool InstructionBuilder<Add>::isInstruction(const Memory& memory, LogicalAddress opAddress){
    return false;
}
