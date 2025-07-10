#include "Gui/Viewport/GLMesh.h"
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    // disable vertex attrib array
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}

void GLMesh::setPosBuffer(std::vector<enzo::bt::Vector3> data)
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    vertexPosData.clear();
    std::cout << "pos data\n-------\n";
    for(auto vector : data)
    {
        vertexPosData.push_back(vector.x());
        vertexPosData.push_back(vector.y());
        vertexPosData.push_back(vector.z());
        std::cout << vector.x() << " " << vector.y() << " " << vector.z() << "\n";
    }

    glBufferData(GL_ARRAY_BUFFER, vertexPosData.size()*sizeof(GLfloat), vertexPosData.data(), GL_STATIC_DRAW);
    unbind();
}

void GLMesh::setIndexBuffer(std::vector<int> pointIndices, std::vector<int> primVertexCounts)
{
    bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    indexData.clear();
    std::cout << "index pointIndices\n-------\n";
    size_t startIndex = 1;

    // create triangle fan from potentially ngon inputs
    std::cout << "size: " << primVertexCounts.size() << "\n";
    for(size_t primNum=0; primNum<primVertexCounts.size(); ++primNum)
    {
        int primVertexCount = primVertexCounts[primNum];

        std::cout << "startIndex: " << startIndex << "\n";
        std::cout << "prim vertex count: " << primVertexCount << "\n";

        for(size_t pointIndex=startIndex; pointIndex+2<startIndex+primVertexCount; ++pointIndex)
        {
            indexData.push_back(pointIndices.at(startIndex-1));
            indexData.push_back(pointIndices.at(pointIndex));
            indexData.push_back(pointIndices.at(pointIndex+1));

            std::cout << pointIndices.at(0) << " " << pointIndices.at(pointIndex) << " " << pointIndices.at(pointIndex+1) << "\n";
        }

        startIndex += primVertexCount;
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
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_INT, 0);
}
