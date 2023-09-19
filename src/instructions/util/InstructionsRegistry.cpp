#include <util/InstructionsRegistry.h>
#include <add.h>
#include <sub.h>
#include <push.h>
#include <mov.h>
#include <nop.h>

InstructionRegistry::InstructionRegistry() {
    initializeInstructionModules();
}

void InstructionRegistry::initializeInstructionModules() {
    addInstruction<Add>();
    addInstruction<Sub>();
    addInstruction<Push>();
    addInstruction<Mov>();
    addInstruction<Nop>();
}

const std::vector<std::unique_ptr<InstructionIfcBuilder>>& InstructionRegistry::getInstructionRegistryVector() const {
    return instructionVector;
}
