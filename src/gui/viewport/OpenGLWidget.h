#include <QOpenGLWidget>
#include <iostream>
#include <QOpenGLFunctions_3_2_Core>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Core
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }
    QSize sizeHint() const override { return QSize(-1, -1); }

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        initializeOpenGLFunctions();
        GLuint vao;
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);

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
    }

};
