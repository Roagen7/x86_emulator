#pragma once

#include <string>
#include <memory>
#include <utility/Widths.h>
#include <basicComponents/Memory.h>
#include <util/InstructionData.h>
class Cpu;

struct LogicalAddress;

class InstructionIfc {

public:
    InstructionIfc(InstructionData&& data) {
        instructionData = data;
    }

    virtual void fetch(Cpu& cpu) = 0;
    virtual void callback(Cpu& cpu) const = 0;
    virtual uint32_t size() const = 0;
    virtual std::string mnemonic() const = 0;

    InstructionData getInstructionData() {
        return instructionData;
    }

protected:
    InstructionData instructionData;
};

class InstructionIfcBuilder {
public:
    virtual std::unique_ptr<InstructionIfc> build(InstructionData&& data) = 0;
    virtual InstructionData parseData(const Memory& memory, LogicalAddress opAddress) = 0;
    virtual bool isInstruction(const Memory& memory, LogicalAddress opAddress) = 0;
    virtual bool isInstruction(Byte byte) = 0;
};

template<typename T>
class InstructionBuilder : public InstructionIfcBuilder {
public:
    std::unique_ptr<InstructionIfc> build(InstructionData&& data) override {
        return std::make_unique<T>(std::move(data));
    }

    InstructionData parseData(const Memory& memory, LogicalAddress opAddress) override {
        return {};
    }

    bool isInstruction(const Memory& memory, LogicalAddress opAddress) override {
        return false;
    }

    bool isInstruction(Byte byte) override {
        return false;
    }
};
