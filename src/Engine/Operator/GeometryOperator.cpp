#include "Engine/Operator/GeometryOperator.h"
#include <optional>

using namespace enzo;

nt::GeometryOperator::GeometryOperator()
{
    // TODO: drive by geometry definition
    maxInputs_=4;
    maxOutputs_=4;

    inputIds_ = std::vector<std::optional<nt::OpId>>(maxInputs_, std::nullopt);
    outputIds_ = std::vector<std::optional<nt::OpId>>(maxOutputs_, std::nullopt);
}

bool nt::GeometryOperator::setInput(unsigned int inputNumber, nt::OpId opId)
{
    if(inputNumber>=maxInputs_)
    {
        return false;
    }
    inputIds_[inputNumber] = opId;

    return true;
}
bool nt::GeometryOperator::setOutput(unsigned int outputNumber, nt::OpId opId)
{

    if(outputNumber>=maxOutputs_)
    {
        return false;
    }
    inputIds_[outputNumber] = opId;
    return true;
}

std::optional<nt::OpId> nt::GeometryOperator::getInput(unsigned int inputNumber) const
{
    if(inputNumber>=maxInputs_)
    {
        return std::nullopt;
    }
    return inputIds_.at(inputNumber);    
}

std::optional<nt::OpId> nt::GeometryOperator::getOutput(unsigned int outputNumber) const
{
    if(outputNumber>=maxOutputs_)
    {
        return std::nullopt;
    }
    return outputIds_.at(outputNumber);    
}


