#include <instructions/InstructionsRegistry.h>
#include <instructions/add.h>
#include <instructions/sub.h>
#include <instructions/push.h>
#include <instructions/mov.h>

InstructionRegistry::InstructionRegistry() {
    initializeInstructionModules();
}

void InstructionRegistry::initializeInstructionModules() {
    addInstruction<Add>();
    addInstruction<Sub>();
    addInstruction<Push>();
    addInstruction<Mov>();
}

const std::vector<std::unique_ptr<InstructionIfcBuilder>>& InstructionRegistry::getInstructionRegistryVector() const {
    return instructionVector;
}
