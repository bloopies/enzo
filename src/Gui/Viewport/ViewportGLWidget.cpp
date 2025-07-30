#include "Gui/Viewport/ViewportGLWidget.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include "Gui/Viewport/GLMesh.h"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <qtimer.h>
#include "Engine/Operator/Geometry.h"

void ViewportGLWidget::initializeGL()
{
    using namespace enzo;
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    enzo::geo::Geometry geo = enzo::geo::Geometry();
    // triangleMesh_ = meshFromGeo(geo);
    triangleMesh_ = std::make_unique<GLMesh>();
    gridMesh_ = std::make_unique<GLGrid>();

    QSurfaceFormat fmt = context()->format();
    std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGLES ? "GLES" : "Desktop") << "\n";
    std::cout << "format: " << (fmt.renderableType() == QSurfaceFormat::OpenGL ? "true" : "false") << "\n";

    // init loop
    QTimer* loopTimer = new QTimer(this);
    connect(loopTimer, &QTimer::timeout, this, QOverload<>::of(&QOpenGLWidget::update));
    loopTimer->start(16);

    // init camera
    curCamera = GLCamera(-10, 5, -10);


    // vertex shader
    const std::string vertexShaderSource = R"(
        #version 330 core
        uniform mat4 uView;
        uniform mat4 uProj;
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aNormal;

        out vec3 Normal;

        void main()
        {
            Normal = aNormal;
            gl_Position = uProj * uView * vec4(aPos, 1.0);
        }
        )";
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
    const std::string fragmentShaderSource = R"(
    #version 330 core
    in vec3 Normal;

    out vec4 FragColor;

    void main()
    {
        // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        FragColor = vec4(Normal, 1.0f);
    }
    )";
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



    constexpr float clearValue = 0.19;
    glClearColor(clearValue, clearValue, clearValue, 1.0f);
}



void ViewportGLWidget::resizeGL(int w, int h)
{
}

void ViewportGLWidget::paintGL()
{


    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


    glm::mat4 projMatrix = glm::perspective(
        glm::radians(45.0f),                  // FOV
        float(width()) / height(),          // aspect ratio
        0.1f,                                 // near plane
        1000.0f                                // far plane
    );

    gridMesh_->useProgram();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProj"), 1, GL_FALSE, glm::value_ptr(projMatrix));
    curCamera.setUniform(glGetUniformLocation(shaderProgram, "uView"));


    gridMesh_->draw();

    glUseProgram(shaderProgram);
    GLint projMLoc = glGetUniformLocation(shaderProgram, "uProj");
    glUniformMatrix4fv(projMLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));

    GLint viewMLoc = glGetUniformLocation(shaderProgram, "uView");
    curCamera.setUniform(viewMLoc);

    triangleMesh_->draw();


}

std::unique_ptr<GLMesh> ViewportGLWidget::meshFromGeo(enzo::geo::Geometry& geometry)
{
    using namespace enzo;

    auto mesh = std::make_unique<GLMesh>();
        
    std::shared_ptr<ga::Attribute> PAttr = geometry.getAttribByName(ga::AttrOwner::POINT, "P");
    ga::AttributeHandleVector3 PAttrHandle = ga::AttributeHandleVector3(PAttr);


    mesh->setPosBuffer(geometry);

    std::shared_ptr<ga::Attribute> pointAttr = geometry.getAttribByName(ga::AttrOwner::VERTEX, "point");
    ga::AttributeHandleInt pointAttrHandle = ga::AttributeHandleInt(pointAttr);

    std::shared_ptr<ga::Attribute> vertexCountAttr = geometry.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
    ga::AttributeHandleInt vertexCountHandle = ga::AttributeHandleInt(vertexCountAttr);

    mesh->setIndexBuffer(pointAttrHandle.getAllValues(), vertexCountHandle.getAllValues());



    return mesh; 
}

void ViewportGLWidget::geometryChanged(enzo::geo::Geometry& geometry)
{
    using namespace enzo;
    std::shared_ptr<ga::Attribute> PAttr = geometry.getAttribByName(ga::AttrOwner::POINT, "P");
    ga::AttributeHandleVector3 PAttrHandle = ga::AttributeHandleVector3(PAttr);

    triangleMesh_->setPosBuffer(geometry);

    std::shared_ptr<ga::Attribute> pointAttr = geometry.getAttribByName(ga::AttrOwner::VERTEX, "point");
    ga::AttributeHandleInt pointAttrHandle = ga::AttributeHandleInt(pointAttr);

    std::shared_ptr<ga::Attribute> vertexCountAttr = geometry.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
    ga::AttributeHandleInt vertexCountHandle = ga::AttributeHandleInt(vertexCountAttr);

    triangleMesh_->setIndexBuffer(pointAttrHandle.getAllValues(), vertexCountHandle.getAllValues());
}
