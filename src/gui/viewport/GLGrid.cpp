#include "gui/viewport/GLGrid.h"
#include <glm/ext/vector_float3.hpp>
#include <iostream>

GLGrid::GLGrid()
{
    initializeOpenGLFunctions();
    init();
}

void GLGrid::init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    initBuffers();

    // unbind vertex array
    glBindVertexArray(0);
}

void GLGrid::initBuffers()
{
    constexpr int gridLen = 20;
    constexpr int gridLines = 11;
    float halfLinesCnt = (gridLines-1)*0.5f;
    for(int i=0; i<gridLines; ++i)
    {
        vertices.push_back(glm::vec3((i-halfLinesCnt)*2,0,-gridLen));
        vertices.push_back(glm::vec3((i-halfLinesCnt)*2,0,gridLen));

        vertices.push_back(glm::vec3(-gridLen,0,(i-halfLinesCnt)*2));
        vertices.push_back(glm::vec3(gridLen,0,(i-halfLinesCnt)*2));

    }

    // create buffer of vertices
    glGenBuffers(1, &vbo);
    // set purpose
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // store data in the buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // gives the shader a way to read 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    // disable vertex attrib array
    glEnableVertexAttribArray(0);
}

void GLGrid::bind()
{
    glBindVertexArray(vao);
}

void GLGrid::unbind()
{
    glBindVertexArray(0);
}

void GLGrid::draw()
{
    bind();
    glDrawArrays(GL_LINES, 0, vertices.size());
}
