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

enzo::nt::OpId enzo::nt::NetworkManager::addOperator()
{

    gopStore_.emplace(++maxOpId_, std::make_unique<GeometryOperator>());
    std::cout << "adding operator " << maxOpId_ << "\n";

    return maxOpId_;
}


enzo::nt::NetworkManager* enzo::nt::NetworkManager::getInstance()
{
    if(instancePtr_==nullptr)
    {
        instancePtr_ = new enzo::nt::NetworkManager();
    }
    return instancePtr_;
}

enzo::nt::GeometryOperator& enzo::nt::NetworkManager::getGeoOperator(nt::OpId opId)
{
    return *gopStore_.at(opId);
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
    std::vector<enzo::nt::OpId> dependencyGraph = getDependencyGraph(opId);
    enzo::geo::Geometry prevGeometry;

    std::shared_ptr<ga::Attribute> PAttr = prevGeometry.getAttribByName(ga::AttrOwner::POINT, "P");
    ga::AttributeHandleVector3 PAttrHandle = ga::AttributeHandleVector3(PAttr);
    PAttrHandle.addValue(bt::Vector3(1.0f, -1.0f, 0.0f));
    PAttrHandle.addValue(bt::Vector3(-1.0f, -1.0f, 0.0f));
    PAttrHandle.addValue(bt::Vector3(-1.0f, 1.0f, 0.0f));
    PAttrHandle.addValue(bt::Vector3(0.0f, 2.0f, 0.0f));
    PAttrHandle.addValue(bt::Vector3(1.0f, 1.0f, 0.0f));

    std::shared_ptr<ga::Attribute> pointAttr = prevGeometry.getAttribByName(ga::AttrOwner::VERTEX, "point");
    ga::AttributeHandleInt pointAttrHandle = ga::AttributeHandleInt(pointAttr);
    pointAttrHandle.addValue(0);
    pointAttrHandle.addValue(1);
    pointAttrHandle.addValue(2);
    pointAttrHandle.addValue(3);
    pointAttrHandle.addValue(4);

    for(enzo::nt::OpId opId : dependencyGraph)
    {
        prevGeometry = cookOp(opId, prevGeometry);
    }
    updateDisplay(prevGeometry);
}

enzo::geo::Geometry enzo::nt::NetworkManager::cookOp(enzo::nt::OpId opId, enzo::geo::Geometry inputGeometry)
{
    std::shared_ptr<ga::Attribute> PAttr = inputGeometry.getAttribByName(ga::AttrOwner::POINT, "P");
    ga::AttributeHandleVector3 PAttrHandle = ga::AttributeHandleVector3(PAttr);
    for(int i=0; i<5; ++i)
    {
        enzo::bt::Vector3 vector = PAttrHandle.getValue(i);
        vector.y()+=1;
        PAttrHandle.setValue(i, vector);
    }
    return inputGeometry;
}

std::vector<enzo::nt::OpId> enzo::nt::NetworkManager::getDependencyGraph(enzo::nt::OpId opId)
{
    std::stack<enzo::nt::OpId> traversalBuffer;
    std::vector<enzo::nt::OpId> traversalGraph;
    traversalBuffer.push(opId);

    while(traversalBuffer.size()!=0)
    {
        enzo::nt::OpId currentOp = traversalBuffer.top();
        std::cout << "cooking node: " << currentOp << "\n";
        traversalBuffer.pop();
        auto inputConnections = getGeoOperator(currentOp).getInputConnections();
        for(auto connection : inputConnections)
        {
            traversalBuffer.push(connection->getInputOpId());
            traversalGraph.push_back(connection->getInputOpId());
        }
    }

    std::reverse(traversalGraph.begin(), traversalGraph.end());
    return traversalGraph;
}


std::optional<enzo::nt::OpId> enzo::nt::NetworkManager::getDisplayOp()
{
    return displayOp_;
}

enzo::nt::NetworkManager* enzo::nt::NetworkManager::instancePtr_ = nullptr;

