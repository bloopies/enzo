#include "gui/viewport/Viewport.h"
#include <qboxlayout.h>
#include <qpushbutton.h>

Viewport::Viewport(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_=new QVBoxLayout();
    openGLWidget_ = new MyGLWidget(this);
    mainLayout_->addWidget(openGLWidget_);

    setLayout(mainLayout_);
}

