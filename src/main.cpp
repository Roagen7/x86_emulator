#include <basicComponents/Register.h>
#include <basicComponents/Cpu.h>
#include <basicComponents/Memory.h>

int main(){
    Memory memory(1024);
    Cpu cpu(memory);
    cpu.tick();
}
