#pragma once

#include <cstdint>
#include <vector>

#include "Widths.h"

class Memory {
public:
    Memory(std::size_t size) {
        bytes.resize(size);
    }

    Memory(const std::vector<Byte> bytes) : bytes(bytes) {};

    template<typename WIDTH_T> 
    WIDTH_T read(Address offset){
        WIDTH_T value{0};
        const auto size = sizeof(WIDTH_T);
        for(auto i = 0u; i < size; i++){
            value <<= 8;
            value += readByte(offset + size - i - 1);
        }
        return value;
    }

    template<typename WIDTH_T>
    void write(Address offset, WIDTH_T value){
        const auto size = sizeof(WIDTH_T);
        for(auto i = 0u; i < size; i++){
            writeByte(offset + i, value & 0xFF);
            value >>= 8;
        }
    }

private:
    std::vector<Byte> bytes;

    void writeByte(Address offset, Byte value){
        bytes[offset % bytes.size()] = value;
    }

    Byte readByte(Address offset){
        return bytes[offset % bytes.size()];
    }
};
