#include "Engine/Operator/GeometryOpDef.h"
#include <stdexcept>
#include <iostream>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include "Engine/Operator/AttributeHandle.h"

bool enzo::nt::GeometryOpDef::outputRequested(unsigned int outputIndex)
{
    // TODO: implement
    return true;
}

const enzo::geo::Geometry& enzo::nt::GeometryOpDef::getInputGeoView(unsigned int inputIndex)
{
    // TODO: implement
    return enzo::geo::Geometry();

}

enzo::geo::Geometry enzo::nt::GeometryOpDef::cloneInputGeo(unsigned int inputIndex)
{
    // TODO: implement
    enzo::nt::GeometryOperator& selfOp = nt::NetworkManager::getGeoOperator(opId_);
    std::vector<std::shared_ptr<const nt::GeometryConnection>> inputConnections = selfOp.getInputConnections();
    if(inputConnections.size()==0)
    {
        std::cout << "no input\n";
        return enzo::geo::Geometry();
    }
    std::shared_ptr<const nt::GeometryConnection> inputConnection = inputConnections.at(inputIndex);
    return nt::NetworkManager::getGeoOperator(inputConnection->getInputOpId()).getOutputGeo(inputConnection->getInputIndex());
}

void enzo::nt::GeometryOpDef::setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry)
{
    if(outputIndex>maxOutputs_)
    {
        throw std::runtime_error("Cannot set output geometry to index > maxOutputs");
    }
    outputGeometry_[outputIndex] = geometry;
}

enzo::nt::GeometryOpDef::GeometryOpDef(enzo::nt::OpId opId)
: opId_{opId}
{
    minInputs_=1;
    maxInputs_=4;
    maxOutputs_=4;
    outputGeometry_ = std::vector<enzo::geo::Geometry>(4, enzo::geo::Geometry());
}

enzo::geo::Geometry& enzo::nt::GeometryOpDef::getOutputGeo(unsigned outputIndex)
{
    if(outputIndex>maxOutputs_)
    {
        throw std::runtime_error("Cannot set output geometry to index > maxOutputs");
    }

    return outputGeometry_.at(outputIndex);
}

void enzo::nt::GeometryOpDef::cookOp()
{
    using namespace enzo;
    std::cout << "COOKING\n";

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = cloneInputGeo(0);

        // ----
        // create geometry start
        // ----
        auto PAttr = geo.getAttribByName(ga::AttrOwner::POINT, "P");
        ga::AttributeHandleVector3 PAttrHandle(PAttr);
        int startPt = PAttrHandle.getSize();
        std::vector<bt::Vector3> pts = {
            {-1,-1,-1},{1,-1,-1},{1,-1,1},{-1,-1,1},
            {-1,1,-1},{1,1,-1},{1,1,1},{-1,1,1},
            {0,2,-1},{0,2,1}
        };
        for (auto& p : pts) PAttrHandle.addValue(p);

        auto pointAttr = geo.getAttribByName(ga::AttrOwner::VERTEX, "point");
        ga::AttributeHandleInt pointAttrHandle(pointAttr);
        std::vector<std::vector<int>> faces = {
            {3,2,6,9,7},{0,1,5,8,4},{0,3,7,4},{1,2,6,5},
            {0,1,2,3},{4,7,9},{4,9,8},{5,6,9},{5,9,8}
        };
        for (auto& f : faces) for (int i : f) pointAttrHandle.addValue(startPt + i);

        auto vertexCountAttr = geo.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
        ga::AttributeHandleInt vertexCountHandle(vertexCountAttr);
        for (auto& f : faces) vertexCountHandle.addValue(f.size());

        // --------

        for(int i=0; i<PAttrHandle.getAllValues().size(); ++i)
        {
            enzo::bt::Vector3 vector = PAttrHandle.getValue(i);
            vector.x()+=2.5;
            PAttrHandle.setValue(i, vector);
        }


        // set output geometry
        setOutputGeometry(0, geo);
    }

    // if(outputRequested(1))
    // {
    //     // create new geometry
    //     const geo::Geometry& geo1 = getInputGeoView(0);
    //     geo::Geometry geo2;

    //     setOutputGeometry(1, geo2);
    // }
}
