#pragma once

#include <vector>

#include <Register.h>

class Fpu {
public:
    RegisterFpu& st(std::size_t index);
    bool push(RegisterFpu val);

private:
    static constexpr auto numRegisters = 8;
    std::vector<RegisterFpu> stack;
};