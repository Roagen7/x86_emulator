#pragma once

#include <string>
#include <memory>

class Cpu;
class Memory;

class IInstruction {

public:
    virtual void fetch(Cpu& cpu) = 0;
    virtual void callback(Cpu& cpu) const = 0;
    virtual uint32_t size() const = 0;
    virtual std::string mnemonic() const = 0;
};

class IInstructionBuilder {
public:
    virtual std::unique_ptr<IInstruction> build() = 0;
    virtual bool isInstruction(const Memory& memory, const Cpu& cpu) = 0;
    virtual bool isInstruction(Byte byte) = 0;
};

template<typename T>
class InstructionBuilder : public IInstructionBuilder {
public:
    std::unique_ptr<IInstruction> build() override {
        return std::make_unique<T>();
    }

    bool isInstruction(const Memory& memory, const Cpu& cpu) override {
        return false;
    }

    bool isInstruction(Byte byte) override {
        return false;
    }
};