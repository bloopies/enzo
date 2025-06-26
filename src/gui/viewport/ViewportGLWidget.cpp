#include "gui/viewport/ViewportGLWidget.h"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <qtimer.h>

void ViewportGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    QSurfaceFormat fmt = context()->format();
    std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGLES ? "GLES" : "Desktop") << "\n";
    std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGL ? "true" : "false") << "\n";
    std::cout << "hello\n";

    // init loop
    QTimer* loopTimer = new QTimer(this);
    connect(loopTimer, &QTimer::timeout, this, QOverload<>::of(&QOpenGLWidget::update));
    loopTimer->start(16);

    // init camera
    curCamera = GLCamera();



    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    GLuint vbo;
    // create buffer of vertices
    glGenBuffers(1, &vbo);
    // set purpose
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // store data in the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind vertex array
    glBindVertexArray(0);


    glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
}



void ViewportGLWidget::resizeGL(int w, int h)
{
}

void ViewportGLWidget::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glm::mat4 projMatrix = glm::perspective(
        glm::radians(45.0f),                  // FOV
        float(width()) / height(),          // aspect ratio
        0.1f,                                 // near plane
        100.0f                                // far plane
    );


    GLint projMLoc = glGetUniformLocation(shaderProgram, "uProj");
    glUniformMatrix4fv(projMLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

    GLint viewMLoc = glGetUniformLocation(shaderProgram, "uView");
    curCamera.setUniform(viewMLoc);



    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
