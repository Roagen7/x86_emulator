#include "Cpu.h"

#include "instructions/add.h"
#include "instructions/sub.h"
#include "instructions/invalid.h"


template<typename NAME>
void addInstruction(std::vector<std::unique_ptr<IInstructionBuilder>>& container){
    container.push_back(std::make_unique<InstructionBuilder<NAME>>());
}

Cpu::Cpu(Memory& memory): memory(memory) {
    initInstructionModules();
}

void Cpu::initInstructionModules(){
    addInstruction<Add>(instructionModules);
    addInstruction<Sub>(instructionModules);
}

void Cpu::reset(){
    
}

std::unique_ptr<IInstruction> Cpu::decode(){
    for(const auto& instructionModule : instructionModules){
        if(!instructionModule->isInstruction(memory, *this)){
            continue;
        }
        return instructionModule->build();
    }
    return std::make_unique<Invalid>();
}

void Cpu::execute(std::unique_ptr<IInstruction> instruction){
    instruction->callback(*this);
}

void Cpu::tick(){
    auto instruction = decode();
    instruction->fetch(*this);
    execute(std::move(instruction));
}