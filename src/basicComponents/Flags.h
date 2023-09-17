#pragma once

#include <utility/Widths.h>

struct Flags {
public:
    struct Flag{
    public:
        bool get(){
            return val_;
        }
        void set(bool val){
            val_ = val;
        }
    private:
        bool val_{false};
    };

    Flag CF, PF, ZF, SF, TF, IF, DF, OF, AF;

    template<typename WIDTH_T>
    void setAddFlags(WIDTH_T arg1, WIDTH_T arg2, bool omitCarry = false){
        WIDTH_T result = arg1 + arg2;
        ZF.set(isZero(result));
        SF.set(isSign(result));
        PF.set(isParity(result & 0xFF));
        OF.set(isOverflow(arg1, arg2, result));
        if(!omitCarry){
            CF.set(isCarry(arg1, result));
        }
        AF.set(isAuxCarry(arg1, arg2));
    }

private:
    template<typename WIDTH_T>
    bool isOverflow(WIDTH_T arg1, WIDTH_T arg2, WIDTH_T result){
        return 
        (isSign(result) && !isSign(arg1) && !isSign(arg2)) ||
        (!isSign(result) && isSign(arg1) && isSign(arg2));
    }
    // aux carry is only for 4 lowest bits
    bool isAuxCarry(Byte arg1, Byte arg2){
        auto arg1lo = arg1 & 0x0F;
        auto arg2lo = arg2 & 0x0F;
        return (arg1lo + arg2lo) >> 4;
    }
    template<typename WIDTH_T>
    bool isCarry(WIDTH_T arg1, WIDTH_T result){
        return (arg1 > result);
    }
    template<typename WIDTH_T>
    bool isZero(WIDTH_T after){
        return after == 0;
    }
    template<typename WIDTH_T>
    bool isSign(WIDTH_T after){
        return (1 << (sizeof(WIDTH_T) * 8u - 1)) & after;
    }   

    // parity is only checked for LSB
    bool isParity(Byte after){
        uint8_t counter = 0;
        for(auto i = 0u; i < sizeof(Byte) * 8; i++){
            counter += (after >> i) & 1;
        }
        return counter % 2 == 0;
    }
};