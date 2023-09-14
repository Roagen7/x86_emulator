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
    uint64_t getTickCounter();

    Register32 eax{"EAX"}, ecx{"ECX"}, edx{"EDX"}, esi{"ESI"}, 
               edi{"EDI"}, ebx{"EBX"}, ebp{"EBP"}, esp{"ESP"};
    Register32 eip{"EIP"};
    Register16 ds{"DS"}, es{"ES"}, fs{"FS"}, gs{"GS"};
    Register16 cs{"CS", resetVector}, ss{"SS", resetVector};

    const Register32& getEip();
    Memory& getMemory();
    Memory& getMemoryConst() const;

private:
    static constexpr auto resetVector{0xFFFF};
    enum Modes {
        REAL,
        PROTECTED
    } mode{REAL};

    Memory& memory;
    uint64_t tickCounter{0u};

    std::vector<std::unique_ptr<IInstructionBuilder>> instructionModules;
    std::unique_ptr<IInstruction> decode();

    void execute(std::unique_ptr<IInstruction> instruction);
    void initInstructionModules();
    void reset();
};


