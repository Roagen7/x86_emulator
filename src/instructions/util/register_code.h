#pragma once

#include <basicComponents/Register.h>
#include <basicComponents/Cpu.h>


// w -> width modifier, w = 1 = wide (16/32 bits), w = 0 (8 bits)
inline Register32& registerCode(Cpu& cpu, Byte threebits, bool w) {
    switch(threebits){
        case 0b000:
            return cpu.eax;
        case 0b001:
            return cpu.ecx;
        case 0b010: 
            return cpu.edx;
        case 0b011:
            return cpu.ebx;
        case 0b100:
            return w ? cpu.esp : cpu.eax;
        case 0b101:
            return w ? cpu.ebp : cpu.ecx;
        case 0b110:
            return w ? cpu.esi : cpu.edx;
        case 0b111:
            return w ? cpu.edi : cpu.ebx;
    }
    // TODO: this shouldn't happen, add exception
    return cpu.eax;
}
