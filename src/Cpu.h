#pragma once

#include <variant>
#include <memory>

#include "Register.h"
#include "Memory.h"
#include "IInstruction.h"

#include "instructions/add.h"

class Cpu {
public:
    Cpu(){
        
    }

    void tick(){
        auto instruction = decode();
        execute(std::move(instruction));
    }
private:
    Register32 eax, ecx, edx, esi, 
               edi, ebx, ebp, esp;
    //Memory& memory;
    
    std::unique_ptr<IInstruction> decode(){
        // TODO: decode logic
    };

    void execute(std::unique_ptr<IInstruction> instruction){
        instruction->callback(*this);
    }
};


