#include <Cpu.h>
#include <instructions/util/instructionsRegistry.h>
#include <iostream>

Cpu::Cpu(Memory& memory): memory(memory), instructionDecoder{registry} {
}

void Cpu::reset(){
    
}

std::unique_ptr<InstructionIfc> Cpu::decode() const {
    auto instructionAddress = LogicalAddress{cs, eip.get<Dword>()};
    return instructionDecoder.decode(memory, instructionAddress);
}

void Cpu::execute(std::unique_ptr<InstructionIfc> instruction){
    instruction->callback(*this);
}

void Cpu::tick(){
    tickCounter++;
    auto instruction = decode();
    if (!instruction) {
        std::cerr << "Invalid instruction\n";
        return;
    }
    eip.set<Dword>(eip.get<Dword>() + instruction->size());
    instruction->fetch(*this);
    execute(std::move(instruction));
}

uint64_t Cpu::getTickCounter(){
    return tickCounter;
}

const Register32& Cpu::getEip(){
    return eip;
}

Memory& Cpu::getMemory(){
    return memory;
}

Memory& Cpu::getMemoryConst() const {
    return memory;
}
