#include "gui/network/SocketGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>

SocketGraphic::SocketGraphic(QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    brushActive_ = QBrush("white");
    brushInactive_ = QBrush("#9f9f9f");
    socketSize_ = 3;
    setAcceptHoverEvents(true);
}

QRectF SocketGraphic::boundingRect() const
{
    float paddingScale = 10;
    auto boundRect = QRect(-socketSize_/2.0f*paddingScale, -socketSize_/2.0f*paddingScale, socketSize_*paddingScale, socketSize_*paddingScale);
    return boundRect;
}

void SocketGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(hovered_ ? brushActive_ : brushInactive_);
    painter->drawEllipse(QPoint(0,0), socketSize_, socketSize_);
 
}

void SocketGraphic::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hovered_ = true;
    update();
}


void SocketGraphic::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hovered_ = false;
    update();
}
