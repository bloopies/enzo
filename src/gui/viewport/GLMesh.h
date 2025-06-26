#pragma once
#include <QOpenGLFunctions_3_2_Core>

class GLMesh
: protected QOpenGLFunctions_3_2_Core
{
public:
    GLMesh();
    GLuint vao;
    GLuint vbo;

    void init();
    void initBuffers();
    void bind();
    void unbind();
    void draw();
};
