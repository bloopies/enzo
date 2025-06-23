#include "gui/network/DisplayFlagButton.h"
#include <QPainter>
#include <qgraphicsitem.h>
#include <qnamespace.h>

DisplayFlagButton::DisplayFlagButton(QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    constexpr float width = 8;
    constexpr float height = 14;
    baseRect_ = QRectF(-width/2.0f, -height/2.0f, width, height);

}

void DisplayFlagButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(disabledColor_));
    constexpr float roundRad = 3;
    painter->drawRoundedRect(baseRect_, roundRad, roundRad);
}

QRectF DisplayFlagButton::boundingRect() const
{
    return baseRect_; 
}

float DisplayFlagButton::getWidth()
{
    return baseRect_.width();
}
