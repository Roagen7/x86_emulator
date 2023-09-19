#pragma once

#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>

#include <utility/Widths.h>
#include <Register.h>

struct LogicalAddress {
    Register16 segment;
    uint32_t offset;

    operator Address() { 
        return segment.get<Word>() * 16u + offset; 
    }
};

class Memory {
public:
    Memory(std::size_t size) {
        bytes.resize(size);
    }

    Memory(const std::string& filename, std::size_t memsize){
        std::ifstream input(filename, std::ios::binary);
        if(!input.is_open()){
            std::cerr << "can't read file " << filename << std::endl;
            return;
        }
        bytes = std::vector<Byte>(
            (std::istreambuf_iterator<char>(input)), 
            std::istreambuf_iterator<char>());
        if(bytes.size() < memsize){
            bytes.resize(memsize);
        }
    }

    Memory(const std::vector<Byte> bytes) : bytes(bytes) {};

    template<typename WIDTH_T> 
    WIDTH_T read(Address offset) const {
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


protected:
    std::vector<Byte> bytes;

    void writeByte(Address offset, Byte value){
        bytes[offset % bytes.size()] = value;
    }

    Byte readByte(Address offset) const {
        return bytes[offset % bytes.size()];
    }
};
