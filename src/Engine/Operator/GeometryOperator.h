#pragma once
#include "Engine/Operator/GeometryConnection.h"
#include "Engine/Types.h"
#include <optional>
#include <memory>

namespace enzo::nt {
void connectOperators(enzo::nt::OpId inputOpId, unsigned int inputIndex, enzo::nt::OpId outputOpId, unsigned int outputIndex);

class GeometryOperator
{
public:
    GeometryOperator();
    // bool setInput(unsigned int inputNumber, nt::OpId opId);
    // bool setOutput(unsigned int outputNumber, nt::OpId opId);
    // std::optional<nt::OpId> getInput(unsigned int inputNumber) const;
    // std::optional<nt::OpId> getOutput(unsigned int outputNumber) const;

    void addInputConnection(std::shared_ptr<nt::GeometryConnection> connection);
    void addOutputConnection(std::shared_ptr<nt::GeometryConnection> connection);



    unsigned int getMaxInputs() const;
    unsigned int getMaxOutputs() const;


private:
    // TODO: avoid duplicate connections
    std::vector<std::shared_ptr<nt::GeometryConnection>> inputConnections_;
    std::vector<std::shared_ptr<nt::GeometryConnection>> outputConnections_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;

};
}
