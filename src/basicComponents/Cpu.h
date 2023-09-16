#pragma once

#include <variant>
#include <memory>

#include <Register.h>
#include <Memory.h>
#include <instructions/InstructionIfc.h>
#include <InstructionDecoder.h>

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

    enum class CpuMode {
        REAL,
        PROTECTED
    };

private:
    static constexpr auto resetVector{0xFFFF};
    CpuMode mode{CpuMode::REAL};

    Memory& memory;
    uint64_t tickCounter{0u};

    std::unique_ptr<InstructionIfc> decode();

    InstructionRegistry registry;
    InstructionDecoder instructionDecoder;
    void execute(std::unique_ptr<InstructionIfc> instruction);
    void reset();
};
