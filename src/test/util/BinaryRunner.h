#pragma once

#include <ranges>

#include "../../main/Memory.h"
#include "../../main/Cpu.h"

class BinaryRunner {
private: 
    static constexpr auto memorySize = 1048576; // 1MB
    
public:
    Cpu cpu;
    Memory memory;

    BinaryRunner(const std::initializer_list<Byte>& binaryCode): memory(memorySize), cpu(memory){
        Address addr = 0;
        for(const auto& bin: binaryCode){
            memory.write(addr++, bin);
        }
    }
    void run(const uint32_t& ticks){
        for(auto i = 0u; i < ticks; i++){
            cpu.tick();
        }
    }
};