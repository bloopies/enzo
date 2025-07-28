#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Operator/OpInfo.h"
#include "Engine/Types.h"
#include <iostream>
#include <memory>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <string>

enzo::nt::OpId enzo::nt::NetworkManager::addOperator(op::OpInfo opInfo)
{

    maxOpId_++;
    std::unique_ptr<GeometryOperator> newOp = std::make_unique<GeometryOperator>(maxOpId_, opInfo);
    newOp->nodeDirtied.connect(
        [this](nt::OpId opId)
        {
            cookOp(opId);

            if(getDisplayOp()==opId)
            {
                enzo::nt::GeometryOperator& displayOp = getGeoOperator(opId);
                updateDisplay(displayOp.getOutputGeo(0));
            }
        });
    gopStore_.emplace(maxOpId_, std::move(newOp));
    std::cout << "adding operator " << maxOpId_ << "\n";

    return maxOpId_;
}


enzo::nt::NetworkManager& enzo::nt::NetworkManager::getInstance()
{
    static enzo::nt::NetworkManager instance;
    return instance;
}

enzo::nt::GeometryOperator& enzo::nt::NetworkManager::getGeoOperator(nt::OpId opId)
{
    std::cout << "gop size middle getter: " << gopStore_.size() <<"\n"; // <- size 0
    auto it = gopStore_.find(opId);
    if(it == gopStore_.end())
    {
        throw std::out_of_range("OpId: " + std::to_string(opId) + " > max opId: " + std::to_string(maxOpId_) + "\n");
    }
    return *it->second;
}

bool enzo::nt::NetworkManager::isValidOp(nt::OpId opId)
{
    auto it = gopStore_.find(opId);
    if( it == gopStore_.end() || it->second==nullptr )
    {
        return false;
    }
    return true;
}

void enzo::nt::NetworkManager::setDisplayOp(OpId opId)
{
    displayOp_=opId;
    
    cookOp(opId);

    enzo::nt::GeometryOperator& displayOp = getGeoOperator(opId);
    updateDisplay(displayOp.getOutputGeo(0));
    displayNodeChanged();
}

void enzo::nt::NetworkManager::cookOp(enzo::nt::OpId opId)
{
    std::vector<enzo::nt::OpId> dependencyGraph = getDependencyGraph(opId);

    for(enzo::nt::OpId dependencyOpId : dependencyGraph)
    {
        enzo::nt::GeometryOperator& op = getGeoOperator(dependencyOpId);
        enzo::op::Context context(dependencyOpId, enzo::nt::nm());
        op.cookOp(context);
    }
}

std::vector<enzo::nt::OpId> enzo::nt::NetworkManager::getDependencyGraph(enzo::nt::OpId opId)
{
    std::stack<enzo::nt::OpId> traversalBuffer;
    std::vector<enzo::nt::OpId> dependencyGraph;
    traversalBuffer.push(opId);
    dependencyGraph.push_back(opId);

    while(traversalBuffer.size()!=0)
    {
        enzo::nt::OpId currentOp = traversalBuffer.top();
        std::cout << "cooking node: " << currentOp << "\n";
        traversalBuffer.pop();
        auto inputConnections = getGeoOperator(currentOp).getInputConnections();
        for(auto connection : inputConnections)
        {
            if(auto connectionPtr = connection.lock())
            {
                traversalBuffer.push(connectionPtr->getInputOpId());
                dependencyGraph.push_back(connectionPtr->getInputOpId());
            }
            else { throw std::runtime_error("Connection weak ptr invalid"); }
        }
    }

    std::reverse(dependencyGraph.begin(), dependencyGraph.end());
    return dependencyGraph;
}


std::optional<enzo::nt::OpId> enzo::nt::NetworkManager::getDisplayOp()
{
    return displayOp_;
}

#ifdef UNIT_TEST
void enzo::nt::NetworkManager::_reset()
{
    std::cout << "resetting network manager\n";

    gopStore_.clear();
    maxOpId_=0;
    displayOp_.reset();
}
#endif

// std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> enzo::nt::NetworkManager::gopStore_;

