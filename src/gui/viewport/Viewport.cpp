#include "gui/viewport/Viewport.h"
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <iostream>
#include <QTimer>

Viewport::Viewport(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_=new QVBoxLayout();
    openGLWidget_ = new MyGLWidget(this);
    mainLayout_->addWidget(openGLWidget_);
    openGLWidget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // mainLayout_->addWidget(new QPushButton("hello world"));
    this->setLayout(mainLayout_);
    // this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //     QTimer::singleShot(100, this, [=] {
    // std::cout << "MyGLWidget size: " << openGLWidget_->width() << " x " << openGLWidget_->height() << std::endl;
    // });


}

