#pragma once
#include <instructions/util/InstructionIfc.h>
#include <vector>
#include <memory>

class InstructionRegistry {
public:
    InstructionRegistry();
    const std::vector<std::unique_ptr<InstructionIfcBuilder>>& getInstructionRegistryVector() const;
private:
    std::vector<std::unique_ptr<InstructionIfcBuilder>> instructionVector;

    void initializeInstructionModules();

    template<typename InstructionName>
    void addInstruction() {
        instructionVector.emplace_back(std::make_unique<InstructionBuilder<InstructionName>>());
    }
};
