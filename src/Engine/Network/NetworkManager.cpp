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

    // ----
    // create geometry start
    // ----
    std::shared_ptr<ga::Attribute> PAttr = prevGeometry.getAttribByName(ga::AttrOwner::POINT, "P");
    ga::AttributeHandleVector3 PAttrHandle(PAttr);
    std::vector<bt::Vector3> pts={
        {-1,-1,-1},{1,-1,-1},{1,-1,1},{-1,-1,1},
        {-1,1,-1},{1,1,-1},{1,1,1},{-1,1,1},
        {0,2,-1},{0,2,1}
    };
    for(auto& p:pts) PAttrHandle.addValue(p);

    std::shared_ptr<ga::Attribute> pointAttr = prevGeometry.getAttribByName(ga::AttrOwner::VERTEX, "point");
    ga::AttributeHandleInt pointAttrHandle(pointAttr);
    std::vector<std::vector<int>> faces={
        {3,2,6,9,7},{0,1,5,8,4},{0,3,7,4},{1,2,6,5},
        {0,1,2,3},{4,7,9},{4,9,8},{5,6,9},{5,9,8}
    };
    for(auto& f:faces) for(int i:f) pointAttrHandle.addValue(i);

    std::shared_ptr<ga::Attribute> vertexCountAttr = prevGeometry.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
    ga::AttributeHandleInt vertexCountHandle(vertexCountAttr);
    for(auto& f:faces) vertexCountHandle.addValue(f.size());

    // --------

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
    

    for(int i=0; i<PAttrHandle.getAllValues().size(); ++i)
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

