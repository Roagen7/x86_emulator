#pragma once

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

    Flag CF, PF, ZF, SF, TF, IF, DF, OF;
};