#include "Gui/Parameters/AbstractSliderParm.h"
#include <QPainter>
#include <QPaintEvent>
#include <iostream>


enzo::ui::AbstractSliderParm::AbstractSliderParm(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    setFixedHeight(20);
    value_ = defaultValue_;

}

void enzo::ui::AbstractSliderParm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);

    QRectF fillRect = event->rect();
    float fillPercent = value_/maxValue_;
    std::cout << "fill percent" << fillPercent << "\n";
    fillRect.adjust(0, 0, -fillRect.width()*(1-fillPercent), 0);
    painter.drawRoundedRect(fillRect, 8, 8);

}


void enzo::ui::AbstractSliderParm::mouseMoveEvent(QMouseEvent *event)
{
    value_ = static_cast<float>(event->pos().x())/rect().width() * maxValue_;
    update();
    // std::cout << "pos x: " << fillPercent << "\n";
}

