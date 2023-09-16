#include <util/InstructionsRegistry.h>
#include <add.h>
#include <sub.h>
#include <push.h>
#include <mov.h>

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
