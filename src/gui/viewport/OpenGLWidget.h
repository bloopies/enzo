#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL() override
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
    }

    void resizeGL(int w, int h) override
    {
        // // Update projection matrix and other size related settings:
        // m_projection.setToIdentity();
        // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    }

    void paintGL() override
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);
    }

};
