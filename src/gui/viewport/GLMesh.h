#pragma once
#include "Engine/Types.h"
#include <GL/gl.h>
#include <QOpenGLFunctions_3_2_Core>

class GLMesh
: protected QOpenGLFunctions_3_2_Core
{
public:
    GLMesh();
    GLuint vao;
    GLuint vertexBuffer;
    GLuint indexBuffer;

    std::vector<GLfloat> vertexPosData;
    std::vector<GLint> indexData;

    void init();
    void initBuffers();
    void setPosBuffer(std::vector<enzo::bt::Vector3> data);
    void setIndexBuffer(std::vector<int> data);
    void bind();
    void unbind();
    void draw();
};
