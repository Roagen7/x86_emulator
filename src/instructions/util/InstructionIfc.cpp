#include "InstructionIfc.h"
#include <basicComponents/Cpu.h>

Address InstructionIfc::getOpcodeAddress(){
    Address realAddress = LogicalAddress{cpu.cs, cpu.eip.get<Dword>()};
    return realAddress - size();
}

InstructionData InstructionIfc::getInstructionData() {
        return instructionData;
}