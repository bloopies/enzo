#include <GL/gl.h>
#include <GL/glext.h>
#include <QOpenGLWidget>
#include <iostream>
#include <QOpenGLFunctions_3_2_Core>
#include "gui/viewport/GLCamera.h"
#include "gui/viewport/GLMesh.h"

class ViewportGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_2_Core
{
public:
    ViewportGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }
    QSize sizeHint() const override { return QSize(-1, -1); }
    GLuint shaderProgram;
    GLCamera curCamera;
    std::unique_ptr<GLMesh> triangleMesh_ ;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
