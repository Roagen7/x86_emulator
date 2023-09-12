#include "Register.h"
#include "Cpu.h"
#include "Memory.h"

int main(){
    Memory memory(1024);
    Cpu cpu(memory);
    cpu.tick();
}