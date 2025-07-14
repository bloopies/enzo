#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include <iostream>
#include <memory>
#include <stack>
#include <algorithm>
#include <string>

enzo::nt::OpId enzo::nt::NetworkManager::addOperator(nt::opConstructor ctorFunc)
{

    maxOpId_++;
    gopStore_.emplace(maxOpId_, std::make_unique<GeometryOperator>(maxOpId_, ctorFunc));
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
    std::cout << "gop size before: " << gopStore_.size() <<"\n";
    displayOp_=opId;
    std::vector<enzo::nt::OpId> dependencyGraph = getDependencyGraph(opId);
    enzo::geo::Geometry prevGeometry;
    std::cout << "size: " << dependencyGraph.size() << "\n";

    for(enzo::nt::OpId dependencyOpId : dependencyGraph)
    {
        cookOp(dependencyOpId);
    }
    std::cout << "gop size middle: " << gopStore_.size() <<"\n"; // <- size: 1
    enzo::nt::GeometryOperator& displayOp = getGeoOperator(opId);
    updateDisplay(displayOp.getOutputGeo(0));
    std::cout << "gop size after: " << gopStore_.size() <<"\n";
}

void enzo::nt::NetworkManager::cookOp(enzo::nt::OpId opId)
{
    enzo::nt::GeometryOperator& op = getGeoOperator(opId);
    op.cookOp();
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
            traversalBuffer.push(connection->getInputOpId());
            dependencyGraph.push_back(connection->getInputOpId());
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

