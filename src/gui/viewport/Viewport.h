#pragma once
#include <qboxlayout.h>
#include <qwidget.h>
#include "gui/viewport/OpenGLWidget.h"

class Viewport
: public QWidget
{
public:
    Viewport(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private:
    QVBoxLayout* mainLayout_;
    ViewportGLWidget* openGLWidget_;
    void resizeEvent(QResizeEvent *event) override;

};
