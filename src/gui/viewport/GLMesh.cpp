#include "gui/viewport/GLMesh.h"
#include <GL/gl.h>
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

    vertexPosData = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, 0.5f, 0.0f
    };

    // store data in the buffer
    glBufferData(GL_ARRAY_BUFFER, vertexPosData.size()*sizeof(GLfloat), vertexPosData.data(), GL_STATIC_DRAW);


    // unbind vertex array
    glBindVertexArray(0);
}

void GLMesh::initBuffers()
{


    indexData =
    {
        0, 1, 2, 1, 2, 3
    };

    // create buffer of vertices
    glGenBuffers(1, &vertexBuffer);
    // set purpose
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // gives the shader a way to read buffer data 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    // disable vertex attrib array
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLint), indexData.data(), GL_STATIC_DRAW);

}

void GLMesh::setPosBuffer(std::vector<enzo::bt::Vector3> data)
{
    vertexPosData.clear();
    for(auto vector : data)
    {
        vertexPosData.push_back(vector.x());
        vertexPosData.push_back(vector.y());
        vertexPosData.push_back(vector.z());
    }

    glBufferData(GL_ARRAY_BUFFER, vertexPosData.size()*sizeof(GLfloat), vertexPosData.data(), GL_STATIC_DRAW);
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
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);
}
