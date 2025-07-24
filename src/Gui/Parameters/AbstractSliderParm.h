#pragma once
#include "Engine/Types.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

namespace enzo::ui
{

class AbstractSliderParm
: public QWidget
{
    Q_OBJECT
public:
    AbstractSliderParm(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setValue(bt::floatT value);

Q_SIGNALS:
    void valueChanged(bt::floatT value); 

private:

    QVBoxLayout* mainLayout_;
    QLabel* valueLabel_;
    bt::floatT value_;
    float defaultValue_=0;
    bool clampMin_ = true;
    bool clampMax_ = true;
    bt::floatT minValue_=-5;
    bt::floatT maxValue_=10;

protected:
void paintEvent(QPaintEvent *event) override;
void mouseMoveEvent(QMouseEvent *event) override;
void mousePressEvent(QMouseEvent *event) override;

};

}

