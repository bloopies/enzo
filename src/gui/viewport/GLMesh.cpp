#include "gui/viewport/GLMesh.h"
#include <iostream>

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

    // unbind vertex array
    glBindVertexArray(0);
}

void GLMesh::initBuffers()
{

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // create buffer of vertices
    glGenBuffers(1, &vbo);
    // set purpose
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // store data in the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // gives the shader a way to read 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    // disable vertex attrib array
    glEnableVertexAttribArray(0);
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
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
