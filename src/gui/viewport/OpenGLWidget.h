#include <GL/gl.h>
#include <GL/glext.h>
#include <QOpenGLWidget>
#include <iostream>
#include <QOpenGLFunctions_3_2_Core>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Core
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }
    QSize sizeHint() const override { return QSize(-1, -1); }
    GLuint vao;
    GLuint shaderProgram;

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        initializeOpenGLFunctions();

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
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";
        // shader type
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // convert source
        const GLchar* vertexShaderSourceC = vertexShaderSource.c_str();
        // create shader object
        glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
        // compile shader object
        glCompileShader(vertexShader);
        
        
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

        QSurfaceFormat fmt = context()->format();
        std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGLES ? "GLES" : "Desktop") << "\n";
        std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGL ? "true" : "false") << "\n";

        glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
    }



    void resizeGL(int w, int h) override
    {
    }

    void paintGL() override
    {
        initializeOpenGLFunctions();
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

};
