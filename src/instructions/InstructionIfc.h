#pragma once

#include <string>
#include <memory>

class Cpu;
class Memory;

class InstructionIfc {

public:
    virtual void fetch(Cpu& cpu) = 0;
    virtual void callback(Cpu& cpu) const = 0;
    virtual uint32_t size() const = 0;
    virtual std::string mnemonic() const = 0;
};

class InstructionIfcBuilder {
public:
    virtual std::unique_ptr<InstructionIfc> build() = 0;
    virtual bool isInstruction(const Memory& memory, const Cpu& cpu) = 0;
    virtual bool isInstruction(Byte byte) = 0;
};

template<typename T>
class InstructionBuilder : public InstructionIfcBuilder {
public:
    std::unique_ptr<InstructionIfc> build() override {
        return std::make_unique<T>();
    }

    bool isInstruction(const Memory& memory, const Cpu& cpu) override {
        return false;
    }

    bool isInstruction(Byte byte) override {
        return false;
    }
};