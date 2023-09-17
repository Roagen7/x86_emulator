#include <utility/InstructionDecoder.h>
#include <basicComponents/Memory.h>
#include <basicComponents/Cpu.h>

InstructionDecoder::InstructionDecoder(const InstructionRegistry& registry) : instructionRegistry(registry) {}

std::unique_ptr<InstructionIfc> InstructionDecoder::decode(LogicalAddress address, Cpu& cpu) const {
    for (const auto& instructionModule : instructionRegistry.getInstructionRegistryVector()){
        if(!instructionModule->isInstruction(cpu.getMemoryConst(), address) &&
        !instructionModule->isInstruction(cpu.getMemoryConst().read<Byte>(address))){
            continue;
        }
        InstructionData data = instructionModule->parseData(cpu.getMemoryConst(), address);
        return instructionModule->build(std::move(data), cpu);
    }
    return nullptr;
}
