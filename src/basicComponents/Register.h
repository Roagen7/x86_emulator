#pragma once

#include <cstdint>
#include <string>

#include <utility/Widths.h>

template<typename MAX_WIDTH_T>
class Register {
public:
    Register(const std::string& mnemonic) : mnemonic(mnemonic) {};
    Register(const std::string& mnemonic, MAX_WIDTH_T reg): mnemonic{mnemonic}, reg(reg) {}

    template<typename WIDTH_T> 
    WIDTH_T get() const {
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

    const std::string& getMnemonic(){
        return mnemonic;
    }
private:
    MAX_WIDTH_T reg{};
    std::string mnemonic;
};

class RegisterFpu {
public:
    template<typename PRECISION_T>
    inline void set(PRECISION_T v){
    }

    template<typename PRECISION_T> 
    inline PRECISION_T get(){
    }

private:
    double value{};
};

template<>
inline double RegisterFpu::get(){
    return value;
}

template<>
inline float RegisterFpu::get(){
    return static_cast<float>(value);
}

template<>
inline void RegisterFpu::set(double v){
    value = v;
}

template<>
inline void RegisterFpu::set(float v){
    value = v;
}

using Register32 = Register<Dword>;
using Register16 = Register<Word>;
