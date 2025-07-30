#pragma once
#include "Engine/Types.h"
#include <GL/gl.h>
#include <QOpenGLFunctions_3_2_Core>
#include <glm/ext/vector_float3.hpp>
#include "Engine/Operator/Geometry.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
};

class GLMesh
: protected QOpenGLFunctions_3_2_Core
{
public:
    GLMesh();
    GLuint vao;
    GLuint vertexBuffer;
    GLuint indexBuffer;

    // std::vector<GLfloat> vertexPosData;
    std::vector<Vertex> vertices;
    std::vector<GLint> indexData;

    void init();
    void initBuffers();
    void setPosBuffer(enzo::geo::Geometry& geometry);
    void setIndexBuffer(std::vector<int> pointIndices, std::vector<int> primVertexCounts);
    void bind();
    void unbind();
    void draw();
};
