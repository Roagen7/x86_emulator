#pragma once

#include <ranges>

#include "../../main/Memory.h"
#include "../../main/Cpu.h"

class BinaryRunner {
private: 
    static constexpr auto codeSize = 1024;
    
public:
    Cpu cpu;
    Memory memory;

    BinaryRunner(const std::initializer_list<Byte>& binaryCode): memory(binaryCode), cpu(memory){}
    void run(const uint32_t& ticks){
        for(auto i = 0u; i < ticks; i++){
            cpu.tick();
        }
    }
};