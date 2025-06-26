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
    initShaderProgram();

    // unbind vertex array
    glBindVertexArray(0);
}

void GLGrid::initShaderProgram()
{
    // vertex shader
    const std::string vertexShaderSource = "#version 330 core\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProj;\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uProj * uView * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";
    // shader type
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // convert source
    const GLchar* vertexShaderSourceC = vertexShaderSource.c_str();
    // create shader object
    glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
    // compile shader object
    glCompileShader(vertexShader);

    
    // log shader error
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    else
    {
        std::cout << "success\n";

    }
    
    
    // fragment shader
    const std::string fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(0.53f, 0.53f, 0.53f, 0.1f);\n"
    "}\n";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentShaderSourceC = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);
    glCompileShader(fragmentShader);

    // create shader program
    shaderProgram = glCreateProgram();
    // attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // link program
    glLinkProgram(shaderProgram);
    
    // delete shaders now that the program is complete
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

void GLGrid::useProgram()
{
    glUseProgram(shaderProgram);
}

void GLGrid::draw()
{
    bind();
    useProgram();
    glDrawArrays(GL_LINES, 0, vertices.size());
}
