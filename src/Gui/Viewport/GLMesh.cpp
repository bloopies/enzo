#include "Gui/Viewport/GLMesh.h"
#include <GL/gl.h>
#include <iostream>
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Types.h"
#include <CGAL/Polygon_mesh_processing/compute_normal.h>
#include "icecream.hpp"



GLMesh::GLMesh()
{
    initializeOpenGLFunctions();
    init();
}

void GLMesh::init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    initBuffers();


    // store data in the buffer
    // glBufferData(GL_ARRAY_BUFFER, vertexPosData.size()*sizeof(GLfloat), vertexPosData.data(), GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLint), indexData.data(), GL_STATIC_DRAW);


    // unbind vertex array
    glBindVertexArray(0);
}

void GLMesh::initBuffers()
{

    // create buffer of vertices
    glGenBuffers(1, &vertexBuffer);
    // set purpose
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // gives the shader a way to read buffer data 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // read normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // disable vertex attrib array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}

void GLMesh::setPosBuffer(enzo::geo::Geometry& geometry)
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    vertices.clear();

    enzo::geo::HeMesh heMesh = geometry.computeHalfEdgeMesh();

    // compute mesh normals
    auto vnormals = heMesh.add_property_map<enzo::geo::V_index, enzo::geo::Vector>("v:normals", CGAL::NULL_VECTOR).first;
    auto fnormals = heMesh.add_property_map<enzo::geo::F_index, enzo::geo::Vector>("f:normals", CGAL::NULL_VECTOR).first;
    namespace PMP = CGAL::Polygon_mesh_processing;

    PMP::compute_normals(
      heMesh, 
      vnormals,
      fnormals,
      PMP::parameters::vertex_point_map(heMesh.points())
    );

    std::shared_ptr<enzo::ga::Attribute> PAttr = geometry.getAttribByName(enzo::ga::AttrOwner::POINT, "P");
    enzo::ga::AttributeHandleVector3 PAttrHandle = enzo::ga::AttributeHandleVector3(PAttr);
    auto pointPositions = PAttrHandle.getAllValues();
    
    std::shared_ptr<enzo::ga::Attribute> pointAttr = geometry.getAttribByName(enzo::ga::AttrOwner::VERTEX, "point");
    enzo::ga::AttributeHandleInt pointAttrHandle = enzo::ga::AttributeHandleInt(pointAttr);
    auto vertexPointIndices = pointAttrHandle.getAllValues();

    std::shared_ptr<enzo::ga::Attribute> vertexCountAttr = geometry.getAttribByName(enzo::ga::AttrOwner::PRIMITIVE, "vertexCount");
    enzo::ga::AttributeHandleInt vertexCountHandle = enzo::ga::AttributeHandleInt(vertexCountAttr);
    std::vector<int> vertexCounts = vertexCountHandle.getAllValues();

    unsigned int vertexCount = 0;

    for (int primIndx=0; primIndx<vertexCounts.size(); ++primIndx)
    {
        for(int i=0; i< vertexCounts[primIndx]; ++i)
        {
            unsigned int pointIndex = vertexPointIndices[vertexCount];
            enzo::bt::Vector3& p = pointPositions[pointIndex];
            IC(vertexCount, pointIndex);
            IC(p.x(), p.y(), p.z());
            vertices.push_back({
                { p.x(),
                  p.y(),
                  p.z()},
                { p.x(),
                  p.y(),
                  p.z()}
            });
            ++vertexCount;
        }

    }

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    unbind();
}

void GLMesh::setIndexBuffer(std::vector<int> pointIndices, std::vector<int> primVertexCounts)
{
    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    indexData.clear();

    unsigned int startVert = 0;

    // create triangle fan from potentially ngon inputs
    for(size_t primNum=0; primNum<primVertexCounts.size(); ++primNum)
    {
        int primVertexCount = primVertexCounts[primNum];


        for(size_t i=0; i<primVertexCount-1; ++i)
        {
            indexData.push_back(startVert);
            indexData.push_back(startVert+i);
            indexData.push_back(startVert+i+1);

        }

        startVert += primVertexCount;
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLint), indexData.data(), GL_STATIC_DRAW);
    unbind();
}


void GLMesh::bind()
{
    glBindVertexArray(vao);
}

void GLMesh::unbind()
{
    glBindVertexArray(0);
}

void GLMesh::draw()
{
    bind();

    // wireframe
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);
}
