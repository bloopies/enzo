#pragma once
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include <variant>



namespace enzo::geo
{
using Kernel = CGAL::Simple_cartesian<double>;
using Point  = Kernel::Point_3;
using Vector   = Kernel::Vector_3;
using HeMesh      = CGAL::Surface_mesh<Point>;
using vertexDescriptor = HeMesh::Vertex_index;
using faceDescriptor = HeMesh::Face_index;
using V_index  = HeMesh::Vertex_index;
using F_index  = HeMesh::Face_index;

class Geometry
{
public:
    Geometry();
    ga::AttributeHandle<int> addIntAttribute(ga::AttributeOwner owner, std::string name);
    ga::AttributeHandle<bt::Vector3> addVector3Attribute(ga::AttributeOwner owner, std::string name);
    std::shared_ptr<ga::Attribute> getAttribByName(ga::AttributeOwner owner, std::string name);
    std::vector<bt::Vector3> derivePointNormals();
    HeMesh computeHalfEdgeMesh();
private:
    using attribVector = std::vector<std::shared_ptr<ga::Attribute>>;
    attribVector& getAttributeStore(ga::AttributeOwner& owner);
    attribVector pointAttributes_;
    attribVector vertexAttributes_;
    attribVector primitiveAttributes_;
    attribVector globalAttributes_;
};
}
