#pragma once
#include <variant>
#include <unordered_map>
#include <string>
#include <utility/Widths.h>

enum class OpPropertyKey {
    MovType,
    WBit,
    DBit,
    Reg1,
    Reg2,
    Mod,
    Value,
    SBit
};

class InstructionData {
public:
    template<typename T>
    void setProperty(OpPropertyKey key, const T& value) {
        propertyMap[key] = value;
    }

    std::variant<bool, Word, Dword, std::string, std::monostate> getProperty(OpPropertyKey key) const;
private:    
    std::unordered_map<OpPropertyKey, std::variant<bool, Word, Dword, std::string, std::monostate>> propertyMap;

};
