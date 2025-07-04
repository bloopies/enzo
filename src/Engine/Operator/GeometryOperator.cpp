#include "Engine/Operator/GeometryOperator.h"
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include <optional>
#include <iostream>

using namespace enzo;

void enzo::nt::connectOperators(enzo::nt::OpId inputOpId, unsigned int inputIndex, enzo::nt::OpId outputOpId, unsigned int outputIndex)
{
    // get network manager
    auto nm = enzo::nt::NetworkManager::getInstance();

    auto inputOp = nm->getGeoOperator(inputOpId);
    auto outputOp = nm->getGeoOperator(outputOpId);

    auto newConnection = std::make_shared<nt::GeometryConnection>(inputOpId, inputIndex, outputOpId, outputIndex); 

    // set output on the upper operator
    outputOp.addOutputConnection(newConnection);

    // set input on the lower operator
    inputOp.addInputConnection(newConnection);
}

nt::GeometryOperator::GeometryOperator()
{
    // TODO: drive by geometry definition
    maxInputs_=4;
    maxOutputs_=4;
}

// bool nt::GeometryOperator::setInput(unsigned int inputNumber, nt::OpId opId)
// {
//     if(inputNumber>=maxInputs_)
//     {
//         return false;
//     }
//     inputIds_[inputNumber] = opId;

//     return true;
// }
// bool nt::GeometryOperator::setOutput(unsigned int outputNumber, nt::OpId opId)
// {

//     if(outputNumber>=maxOutputs_)
//     {
//         return false;
//     }
//     inputIds_[outputNumber] = opId;
//     return true;
// }

void nt::GeometryOperator::addInputConnection(std::shared_ptr<nt::GeometryConnection> connection)
{
    inputConnections_.push_back(connection); 
}

void nt::GeometryOperator::addOutputConnection(std::shared_ptr<nt::GeometryConnection> connection)
{
    std::cout << "Output connection added\nConnecting ops " << connection->getInputOpId() << " -> " << connection->getOutputOpId() << "\n";
    std::cout << "Connecting index " << connection->getInputIndex() << " -> " << connection->getOutputIndex() << "\n";
    outputConnections_.push_back(connection); 
}


// std::optional<nt::OpId> nt::GeometryOperator::getInput(unsigned int inputNumber) const
// {
//     if(inputNumber>=maxInputs_)
//     {
//         return std::nullopt;
//     }
//     return inputIds_.at(inputNumber);    
// }

// std::optional<nt::OpId> nt::GeometryOperator::getOutput(unsigned int outputNumber) const
// {
//     if(outputNumber>=maxOutputs_)
//     {
//         return std::nullopt;
//     }
//     return outputIds_.at(outputNumber);    
// }


unsigned int nt::GeometryOperator::getMaxInputs() const
{
    return maxInputs_;
}
unsigned int nt::GeometryOperator::getMaxOutputs() const
{
    return maxOutputs_;
}
