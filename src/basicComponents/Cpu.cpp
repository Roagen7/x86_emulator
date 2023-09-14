#include <Cpu.h>

#include <instructions/add.h>
#include <instructions/sub.h>
#include <instructions/push.h>
#include <instructions/invalid.h>

template<typename NAME>
void addInstruction(std::vector<std::unique_ptr<InstructionIfcBuilder>>& container){
    container.push_back(std::make_unique<InstructionBuilder<NAME>>());
}

Cpu::Cpu(Memory& memory): memory(memory) {
    initInstructionModules();
}

void Cpu::initInstructionModules(){
    addInstruction<Add>(instructionModules);
    addInstruction<Sub>(instructionModules);
    addInstruction<Push>(instructionModules);
}

void Cpu::reset(){
    
}

std::unique_ptr<InstructionIfc> Cpu::decode(){
    auto instructionAddress = LogicalAddress{cs, eip.get<Dword>()};
    for(const auto& instructionModule : instructionModules){
        if(!instructionModule->isInstruction(memory, *this) &&
        !instructionModule->isInstruction(memory.read<Byte>(instructionAddress))){
            continue;
        }
        return instructionModule->build();
    }
    return std::make_unique<Invalid>();
}

void Cpu::execute(std::unique_ptr<InstructionIfc> instruction){
    instruction->callback(*this);
}

void Cpu::tick(){
    tickCounter++;
    auto instruction = decode();
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
