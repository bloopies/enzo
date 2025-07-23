#include "Gui/Parameters/AbstractSliderParm.h"
#include "Engine/Types.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <iostream>
#include <qboxlayout.h>
#include <qnamespace.h>
#include <algorithm>
#include <string>


enzo::ui::AbstractSliderParm::AbstractSliderParm(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    // tells qt to style the widget even though it's a Q_OBJECT
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(24);
    value_ = defaultValue_;
    
    mainLayout_ = new QVBoxLayout();
    setLayout(mainLayout_);

    valueLabel_ = new QLabel();
    valueLabel_->setAlignment(Qt::AlignCenter);
    valueLabel_->setStyleSheet("background-color: none;");
    setProperty("type", "SliderParm");
    setStyleSheet(R"(
                  QWidget[type="SliderParm"]
                  {
                      border-radius: 6px;
                      border: 1px solid #383838;
                  }
                  )");
    mainLayout_->addWidget(valueLabel_);

    setValue(value_);
}

void enzo::ui::AbstractSliderParm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#383838"));

    QRectF fillRect = event->rect();
    float fillPercent = value_/maxValue_;
    std::cout << "fill percent" << fillPercent << "\n";
    float margin = 3;
    fillRect.adjust(margin, margin, std::max<float>(-fillRect.width()+margin, -fillRect.width()*(1-fillPercent)-margin), -margin);
    painter.drawRoundedRect(fillRect, 6, 6);

}

void enzo::ui::AbstractSliderParm::setValue(bt::floatT value)
{
    // if(value_==value)
    //     return;

    if(clampMin_ && value<minValue_) { value = minValue_; }
    if(clampMax_ && value>maxValue_) { value = maxValue_; }

    value_ = value;
    update();
    QString valStr = QString::number(value);
    valStr.truncate(4);
    valueLabel_->setText(valStr);

    valueChanged(value_);

}


void enzo::ui::AbstractSliderParm::mouseMoveEvent(QMouseEvent *event)
{
    setValue(static_cast<float>(event->pos().x())/rect().width() * maxValue_);
}

void enzo::ui::AbstractSliderParm::mousePressEvent(QMouseEvent *event)
{
    setValue(static_cast<float>(event->pos().x())/rect().width() * maxValue_);
}

