#pragma once

#include <cstdint>

#include "Widths.h"

template<typename MAX_WIDTH_T>
class Register {
public:
    Register() = default;
    Register(MAX_WIDTH_T reg): reg(reg) {}

    template<typename WIDTH_T> 
    WIDTH_T get(){
        return reg & (-1 >> ((sizeof(MAX_WIDTH_T) - sizeof(WIDTH_T))* 8u));
    }

    template<typename WIDTH_T, uint8_t OFFSET_B>
    void set(const WIDTH_T& value){
        reg &= (-1 << (((sizeof(WIDTH_T) + OFFSET_B)*8u))) | ~(-1 << (OFFSET_B * 8u));
        reg |= (value << (OFFSET_B * 8u));
    }

    template<typename WIDTH_T>
    void set(const WIDTH_T& value){
        reg &= (-1 << (sizeof(WIDTH_T)* 8u));
        reg |= value;
    }

private:
    MAX_WIDTH_T reg{};
};

using Register32 = Register<Dword>;
using Register16 = Register<Word>;
   