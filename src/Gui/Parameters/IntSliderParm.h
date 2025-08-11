#pragma once
#include "Engine/Types.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPen>

namespace enzo::ui
{

class IntSliderParm
: public QWidget
{
    Q_OBJECT
public:
    IntSliderParm(bt::intT value, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setValue(bt::intT value);

Q_SIGNALS:
    void valueChanged(bt::intT value); 

private:

    QVBoxLayout* mainLayout_;
    QLabel* valueLabel_;
    bt::intT value_;
    bool clampMin_ = true;
    bool clampMax_ = true;
    bt::intT minValue_=-5;
    bt::intT maxValue_=10;

    QPen notchPen_;
    static constexpr int notchWidth = 2;

    void setValueImpl(bt::intT value);

protected:
void paintEvent(QPaintEvent *event) override;
void mouseMoveEvent(QMouseEvent *event) override;
void mousePressEvent(QMouseEvent *event) override;

};

}

