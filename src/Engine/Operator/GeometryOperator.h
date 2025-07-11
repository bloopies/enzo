#pragma once
#include "Engine/Operator/GeometryConnection.h"
#include "Engine/Operator/GeometryOpDef.h"
#include "Engine/Types.h"
#include <optional>
#include <memory>

namespace enzo::nt {
void connectOperators(enzo::nt::OpId inputOpId, unsigned int inputIndex, enzo::nt::OpId outputOpId, unsigned int outputIndex);

class GeometryOperator
{
public:
    GeometryOperator(enzo::nt::OpId opId, enzo::nt::GeometryOpDef* (*ctorFunc)(enzo::nt::OpId));

    // disable copying
    GeometryOperator(const GeometryOperator&)            = delete;
    GeometryOperator& operator=(const GeometryOperator&) = delete;

    void cookOp();
    geo::Geometry& getOutputGeo(unsigned outputIndex);

    void addInputConnection(std::shared_ptr<nt::GeometryConnection> connection);
    void addOutputConnection(std::shared_ptr<nt::GeometryConnection> connection);
    std::vector<std::shared_ptr<const GeometryConnection>> getInputConnections() const;
    std::vector<std::shared_ptr<const GeometryConnection>> getOutputConnections() const;



    unsigned int getMaxInputs() const;
    unsigned int getMaxOutputs() const;


private:
    // TODO: avoid duplicate connections
    std::vector<std::shared_ptr<nt::GeometryConnection>> inputConnections_;
    std::vector<std::shared_ptr<nt::GeometryConnection>> outputConnections_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;
    std::unique_ptr<enzo::nt::GeometryOpDef> opDef_;
    enzo::nt::OpId opId_;
};
}
