#include "Engine/Operator/Context.h"
#include "Engine/Network/NetworkManager.h"
#include <iostream>


enzo::op::Context::Context(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager)
: opId_{opId}, networkManager_(networkManager)
{

}

enzo::geo::Geometry enzo::op::Context::cloneInputGeo(unsigned int inputIndex)
{
    // TODO: implement
    enzo::nt::GeometryOperator& selfOp = networkManager_.getGeoOperator(opId_);
    std::vector<std::shared_ptr<const nt::GeometryConnection>> inputConnections = selfOp.getInputConnections();
    if(inputConnections.size()==0)
    {
        std::cout << "no input\n";
        return enzo::geo::Geometry();
    }
    std::shared_ptr<const nt::GeometryConnection> inputConnection = inputConnections.at(inputIndex);
    return networkManager_.getGeoOperator(inputConnection->getInputOpId()).getOutputGeo(inputConnection->getInputIndex());
}

