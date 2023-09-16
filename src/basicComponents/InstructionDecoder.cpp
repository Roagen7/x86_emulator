#include <basicComponents/InstructionDecoder.h>
#include <basicComponents/Memory.h>

InstructionDecoder::InstructionDecoder(const InstructionRegistry& registry) : instructionRegistry(registry) {}

std::unique_ptr<InstructionIfc> InstructionDecoder::decode(const Memory& memory, LogicalAddress address) const {
    for (const auto& instructionModule : instructionRegistry.getInstructionRegistryVector()){
        if(!instructionModule->isInstruction(memory, address) &&
        !instructionModule->isInstruction(memory.read<Byte>(address))){
            continue;
        }
        return instructionModule->build();
    }
    return nullptr;
}
