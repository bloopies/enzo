#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include <memory>
#include <oneapi/tbb/task_group.h>
#include <stdexcept>
#include <string>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include "icecream.hpp"

using namespace enzo;
geo::Geometry::Geometry()
{
    addVector3Attribute(ga::AttrOwner::POINT, "P");
    addIntAttribute(ga::AttrOwner::VERTEX, "point");
    addIntAttribute(ga::AttrOwner::PRIMITIVE, "vertexCount");
}

enzo::geo::HeMesh geo::Geometry::computeHalfEdgeMesh()
{
    HeMesh heMesh;

    std::shared_ptr<enzo::ga::Attribute> PAttr = getAttribByName(enzo::ga::AttrOwner::POINT, "P");
    enzo::ga::AttributeHandleVector3 PAttrHandle = enzo::ga::AttributeHandleVector3(PAttr);
    auto pointPositions = PAttrHandle.getAllValues();
    
    std::shared_ptr<enzo::ga::Attribute> pointAttr = getAttribByName(enzo::ga::AttrOwner::VERTEX, "point");
    enzo::ga::AttributeHandleInt pointAttrHandle = enzo::ga::AttributeHandleInt(pointAttr);
    auto vertexPointIndices = pointAttrHandle.getAllValues();

    std::shared_ptr<enzo::ga::Attribute> vertexCountAttr = getAttribByName(enzo::ga::AttrOwner::PRIMITIVE, "vertexCount");
    enzo::ga::AttributeHandleInt vertexCountHandle = enzo::ga::AttributeHandleInt(vertexCountAttr);
    auto vertexCounts = vertexCountHandle.getAllValues();

    int vertexIndex = 0;
    std::vector<geo::vertexDescriptor> createdPoints;
    createdPoints.reserve(pointPositions.size());
    std::vector<geo::vertexDescriptor> facePoints;
    facePoints.reserve(16);

    for(auto pointPos : pointPositions)
    {
        enzo::geo::vertexDescriptor point = heMesh.add_vertex(geo::Point(pointPos.x(), pointPos.y(), pointPos.z()));
        createdPoints.push_back(point);
    }

    CGAL::Polygon_mesh_processing::orient(heMesh);

    // iterate through each prim
    for(int primIndx=0; primIndx<vertexCounts.size(); ++primIndx)
    {
        facePoints.clear();

        // represents how many vertices are in a primitive
        auto vertexCount = vertexCounts[primIndx];

        // create primtive vertices
        for(int i=0; i<vertexCount; ++i)
        {
            auto pointIndex = vertexPointIndices.at(vertexIndex);
            facePoints.push_back(createdPoints[pointIndex]);
            ++vertexIndex;
        }

        // debug
        std::cout << "Primitive " << primIndx << " has " << vertexCount << " vertices: ";
        for (auto& v : facePoints)
        {
            auto pt = heMesh.point(v);
            std::cout << "(" << pt.x() << ", " << pt.y() << ", " << pt.z() << ") ";
        }
        std::cout << std::endl;

        std::cout << "Point indices: ";
        for (int i = 0; i < vertexCount; ++i) {
            int pointIndex = vertexPointIndices.at(vertexIndex - vertexCount + i);
            std::cout << pointIndex << " ";
        }
        std::cout << std::endl;
        // debug

        auto face = heMesh.add_face(facePoints);
        if (face != HeMesh::null_face()) {
            // validFaceIndices.push_back(enzo::geo::F_index(primIndx));
        } else {
            // throw std::runtime_error("Warning: Face creation failed at primitive " + std::to_string(primIndx));
        }
    }


    return heMesh;
}


ga::AttributeHandle<int> geo::Geometry::addIntAttribute(ga::AttributeOwner owner, std::string name)
{
    auto newAttribute = std::make_shared<ga::Attribute>(name, ga::AttrType::intT);
    getAttributeStore(owner).push_back(newAttribute);
    return ga::AttributeHandle<int>(newAttribute);
}

ga::AttributeHandle<bt::Vector3> geo::Geometry::addVector3Attribute(ga::AttributeOwner owner, std::string name)
{
    auto newAttribute = std::make_shared<ga::Attribute>(name, ga::AttrType::vectorT);
    getAttributeStore(owner).push_back(newAttribute);
    return ga::AttributeHandle<bt::Vector3>(newAttribute);
}

std::vector<std::shared_ptr<ga::Attribute>>& geo::Geometry::getAttributeStore(ga::AttributeOwner& owner)
{
    switch(owner)
    {
        case ga::AttributeOwner::POINT:
            return pointAttributes_;
            break;
        case ga::AttributeOwner::VERTEX:
            return vertexAttributes_;
            break;
        case ga::AttributeOwner::PRIMITIVE:
            return primitiveAttributes_;
            break;
        case ga::AttributeOwner::GLOBAL:
            return globalAttributes_;
            break;
        default:
            throw std::runtime_error("Unexpected, owner could not be found");
    }
}


std::shared_ptr<ga::Attribute> geo::Geometry::getAttribByName(ga::AttributeOwner owner, std::string name)
{
    auto& vector = getAttributeStore(owner);
    for(auto it=vector.begin(); it!=vector.end(); ++it)
    {
        if((*it)->getName()==name)
        {
            return (*it);
        }
    }
    return nullptr;
}

