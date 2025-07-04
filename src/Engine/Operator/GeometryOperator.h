#pragma once
#include "Engine/Types.h"
#include <optional>

namespace enzo::nt {

class GeometryOperator
{
public:
    GeometryOperator();
    bool setInput(unsigned int inputNumber, nt::OpId opId);
    bool setOutput(unsigned int outputNumber, nt::OpId opId);
    std::optional<nt::OpId> getInput(unsigned int inputNumber) const;
    std::optional<nt::OpId> getOutput(unsigned int outputNumber) const;

private:
    std::vector<std::optional<nt::OpId>> inputIds_;
    std::vector<std::optional<nt::OpId>> outputIds_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;

};
}
