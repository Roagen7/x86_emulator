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
    InstructionIfc(InstructionData&& data, Cpu& cpu): instructionData(data), cpu(cpu) {
    }

    virtual void fetch() = 0;
    virtual void callback() const = 0;
    virtual uint32_t size() const = 0;
    virtual std::string mnemonic() const = 0;

    Address getOpcodeAddress();
    InstructionData getInstructionData();

protected:
    InstructionData instructionData;
    Cpu& cpu;
};

class InstructionIfcBuilder {
public:
    virtual std::unique_ptr<InstructionIfc> build(InstructionData&& data, Cpu& cpu) = 0;
    virtual InstructionData parseData(const Memory& memory, LogicalAddress opAddress) = 0;
    virtual bool isInstruction(const Memory& memory, LogicalAddress opAddress) = 0;
    virtual bool isInstruction(Byte byte) = 0;
};

template<typename T>
class InstructionBuilder : public InstructionIfcBuilder {
public:
    std::unique_ptr<InstructionIfc> build(InstructionData&& data, Cpu& cpu) override {
        return std::make_unique<T>(std::move(data), cpu);
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
