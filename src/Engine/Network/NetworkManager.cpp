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

enzo::nt::OpId enzo::nt::NetworkManager::addOperator()
{

    maxOpId_++;
    gopStore_.emplace(maxOpId_, std::make_unique<GeometryOperator>(maxOpId_));
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
    if(opId>gopStore_.size())
    {
        throw std::out_of_range("OpId: " + std::to_string(opId) + " > max opId: " + std::to_string(maxOpId_) + "\n");
    }
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
    // std::shared_ptr<ga::Attribute> PAttr = prevGeometry.getAttribByName(ga::AttrOwner::POINT, "P");
    // ga::AttributeHandleVector3 PAttrHandle(PAttr);
    // std::vector<bt::Vector3> pts={
    //     {-1,-1,-1},{1,-1,-1},{1,-1,1},{-1,-1,1},
    //     {-1,1,-1},{1,1,-1},{1,1,1},{-1,1,1},
    //     {0,2,-1},{0,2,1}
    // };
    // for(auto& p:pts) PAttrHandle.addValue(p);

    // std::shared_ptr<ga::Attribute> pointAttr = prevGeometry.getAttribByName(ga::AttrOwner::VERTEX, "point");
    // ga::AttributeHandleInt pointAttrHandle(pointAttr);
    // std::vector<std::vector<int>> faces={
    //     {3,2,6,9,7},{0,1,5,8,4},{0,3,7,4},{1,2,6,5},
    //     {0,1,2,3},{4,7,9},{4,9,8},{5,6,9},{5,9,8}
    // };
    // for(auto& f:faces) for(int i:f) pointAttrHandle.addValue(i);

    // std::shared_ptr<ga::Attribute> vertexCountAttr = prevGeometry.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
    // ga::AttributeHandleInt vertexCountHandle(vertexCountAttr);
    // for(auto& f:faces) vertexCountHandle.addValue(f.size());

    // --------

    std::cout << "size: " << dependencyGraph.size() << "\n";
    for(enzo::nt::OpId dependencyOpId : dependencyGraph)
    {
        cookOp(dependencyOpId);
    }
    enzo::nt::GeometryOperator& displayOp = getGeoOperator(opId);
    updateDisplay(displayOp.getOutputGeo(0));
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

enzo::nt::NetworkManager* enzo::nt::NetworkManager::instancePtr_ = nullptr;

