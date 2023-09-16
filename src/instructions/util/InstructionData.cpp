#include <instructions/util/InstructionData.h>

std::variant<bool, Word, Dword, std::string, std::monostate> InstructionData::getProperty(OpPropertyKey key) const {
    if (!propertyMap.count(key)) {
        return std::monostate{};
    }
    return propertyMap.at(key);
}
