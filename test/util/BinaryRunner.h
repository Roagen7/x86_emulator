#pragma once

#include <ranges>

#include <basicComponents/Memory.h>
#include <basicComponents/Cpu.h>

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

    BinaryRunner(const std::string& filename): memory(filename, memorySize), cpu(memory){}

    void run(const uint32_t& ticks){
        for(auto i = 0u; i < ticks; i++){
            cpu.tick();
        }
    }
};
