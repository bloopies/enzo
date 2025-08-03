#pragma once
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include "Engine/Operator/AttributeHandle.h"
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
    Geometry(const Geometry& other);
    ga::AttributeHandle<int> addIntAttribute(ga::AttributeOwner owner, std::string name);
    ga::AttributeHandle<bt::Vector3> addVector3Attribute(ga::AttributeOwner owner, std::string name);
    // TODO: return weak ptr
    std::shared_ptr<ga::Attribute> getAttribByName(ga::AttributeOwner owner, std::string name);
    std::vector<bt::Vector3> derivePointNormals();
    HeMesh computeHalfEdgeMesh();
    // returns the first vertex of the primitive
    void addFace(std::initializer_list<ga::Offset> pointOffsets);

    ga::Offset getPrimStartVertex(ga::Offset primOffset) const;
    bt::Vector3 getPosFromVert(ga::Offset vertexOffset) const;
    bt::Vector3 getPointPos(ga::Offset pointOffset) const;
    unsigned int getPrimVertCount(ga::Offset primOffset) const;
    ga::Offset getNumPrims() const;
    ga::Offset getNumVerts() const;
    void computePrimStartVertices();
private:
    using attribVector = std::vector<std::shared_ptr<ga::Attribute>>;
    attribVector& getAttributeStore(ga::AttributeOwner& owner);

    attribVector deepCopyAttributes(attribVector source);

    attribVector pointAttributes_;
    attribVector vertexAttributes_;
    attribVector primitiveAttributes_;
    attribVector globalAttributes_;

    std::vector<ga::Offset> primStarts_;

    // handles
    enzo::ga::AttributeHandleInt vertexCountHandlePrim_;
    enzo::ga::AttributeHandleInt pointOffsetHandleVert_;
    enzo::ga::AttributeHandleVector3 posHandlePoint_;
};
}
