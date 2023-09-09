#include "src/Register.h"
#include "src/Cpu.h"
#include "src/Memory.h"




int main(){
    Cpu cpu;
    Memory memory(1024);
    auto y = InstructionBuilder<Add>().isInstruction(memory, cpu);

    //std::unique_ptr<IInstruction> addBuilder = std::make_unique<Add>();
    //auto in = instr.build();
    //Memory memory(1024u);
    // Cpu cpu;
    Register32 eax;
    eax.set<Dword>(0xFFDEFEC8);
    eax.set<Word>(0xBEEF);
    eax.set<Byte>(0xCC);
    eax.set<Byte,1>(0xDD);
    (void)0;
}