#pragma once
#include <instructions/util/InstructionIfc.h>
#include <instructions/util/InstructionsRegistry.h>
#include <vector>
#include <memory>

class Memory;
struct LogicalAddress;

class InstructionDecoder {
public:
    InstructionDecoder(const InstructionRegistry& registry);
    std::unique_ptr<InstructionIfc> decode(const Memory& memory, LogicalAddress address) const;
private:
    const InstructionRegistry& instructionRegistry;
};
