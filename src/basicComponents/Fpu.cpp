#include <Fpu.h>

RegisterFpu& Fpu::st(std::size_t index){
    return stack[stack.size() - index - 1];
}

bool Fpu::push(RegisterFpu val){
    if(stack.size() == numRegisters) {
        return false;
    }
    stack.push_back(val);
    return true;
}
