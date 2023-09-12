#pragma once

#include <variant>
#include <memory>

#include "Register.h"
#include "Memory.h"
#include "IInstruction.h"

class Cpu {
public:
    Cpu(Memory& memory);
    void tick();

private:
    static constexpr auto resetVector{0xFFFF};
    enum Modes {
        REAL,
        PROTECTED
    } mode{REAL};

    Memory& memory;
    Register32 eax, ecx, edx, esi, 
               edi, ebx, ebp, esp;
    Register16 ss, ds, es, fs, gs;
    Register16 cs{resetVector};

    std::vector<std::unique_ptr<IInstructionBuilder>> instructionModules;
    std::unique_ptr<IInstruction> decode();

    void execute(std::unique_ptr<IInstruction> instruction);
    void initInstructionModules();
    void reset();
};


