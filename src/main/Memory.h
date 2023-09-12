#pragma once

#include <cstdint>
#include <vector>

#include "Widths.h"

class Memory {
public:
    Memory(std::size_t size){
        //bytes.reserve(size);
    }


private:
    std::vector<Byte> bytes;
};
