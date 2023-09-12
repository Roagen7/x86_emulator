#include "src/Register.h"
#include "src/Cpu.h"
#include "src/Memory.h"

int main(){
    Memory memory(1024);
    Cpu cpu(memory);
    cpu.tick();
}