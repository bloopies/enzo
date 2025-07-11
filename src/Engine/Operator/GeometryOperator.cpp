#include "Engine/Operator/GeometryOperator.h"
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include <optional>
#include "Engine/Operator/GOP_test.h"
#include <iostream>

using namespace enzo;

void enzo::nt::connectOperators(enzo::nt::OpId inputOpId, unsigned int inputIndex, enzo::nt::OpId outputOpId, unsigned int outputIndex)
{
    auto& inputOp = nt::NetworkManager::getGeoOperator(inputOpId);
    auto& outputOp = nt::NetworkManager::getGeoOperator(outputOpId);

    auto newConnection = std::make_shared<nt::GeometryConnection>(inputOpId, inputIndex, outputOpId, outputIndex); 

    // set output on the upper operator
    inputOp.addOutputConnection(newConnection);

    // set input on the lower operator
    outputOp.addInputConnection(newConnection);
}

nt::GeometryOperator::GeometryOperator(enzo::nt::OpId opId, enzo::nt::GeometryOpDef* (*ctorFunc)(enzo::nt::OpId))
: opId_{opId}, opDef_(ctorFunc(opId))
{
    // TODO: drive by geometry definition
    maxInputs_=4;
    maxOutputs_=4;
}

void enzo::nt::GeometryOperator::cookOp()
{
    opDef_->cookOp();
}

geo::Geometry& enzo::nt::GeometryOperator::getOutputGeo(unsigned outputIndex)
{
    return opDef_->getOutputGeo(outputIndex);
}

void nt::GeometryOperator::addInputConnection(std::shared_ptr<nt::GeometryConnection> connection)
{
    std::cout << "Input connection added\nConnecting ops " << connection->getInputOpId() << " -> " << connection->getOutputOpId() << "\n";
    std::cout << "Connecting index " << connection->getInputIndex() << " -> " << connection->getOutputIndex() << "\n";
    inputConnections_.push_back(connection); 
    std::cout << "size: " << inputConnections_.size() << "\n";
}

void nt::GeometryOperator::addOutputConnection(std::shared_ptr<nt::GeometryConnection> connection)
{
    std::cout << "Output connection added\nConnecting ops " << connection->getInputOpId() << " -> " << connection->getOutputOpId() << "\n";
    std::cout << "Connecting index " << connection->getInputIndex() << " -> " << connection->getOutputIndex() << "\n";
    outputConnections_.push_back(connection); 
    std::cout << "size: " << outputConnections_.size() << "\n";
}

std::vector<std::shared_ptr<const nt::GeometryConnection>> nt::GeometryOperator::getInputConnections() const
{
    std::vector<std::shared_ptr<const nt::GeometryConnection>> inputConnections;
    for(std::shared_ptr<nt::GeometryConnection> connection : inputConnections_)
    {
        inputConnections.push_back(connection);
    }
    return inputConnections;
}

std::vector<std::shared_ptr<const nt::GeometryConnection>> nt::GeometryOperator::getOutputConnections() const
{
    std::vector<std::shared_ptr<const nt::GeometryConnection>> outputConnections;
    for(std::shared_ptr<nt::GeometryConnection> connection : outputConnections_)
    {
        outputConnections.push_back(connection);
    }
    return outputConnections;
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
