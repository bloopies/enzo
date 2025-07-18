#pragma once
#include <QWidget>

namespace enzo::ui
{

class AbstractSliderParm
: public QWidget
{
public:
    AbstractSliderParm(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    float value_;
    float defaultValue_=0;
    float minValue_;
    float maxValue_=10;

protected:
void paintEvent(QPaintEvent *event) override;
void mouseMoveEvent(QMouseEvent *event) override;

};

}

