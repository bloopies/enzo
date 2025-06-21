#include "gui/network/SocketGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>

SocketGraphic::SocketGraphic(SocketGraphic::SocketType type, QGraphicsItem *parent)
: QGraphicsItem(parent), type_{type}
{
    brushActive_ = QBrush("white");
    brushInactive_ = QBrush("#9f9f9f");
    socketSize_ = 3;
    setAcceptHoverEvents(true);
}

QRectF SocketGraphic::boundingRect() const
{
    float paddingScale = 10;
    auto boundRect = QRect(
        -socketSize_/2.0f*paddingScale, 
        type_==SocketType::Input ? -socketSize_/2.0f*paddingScale : 0,
        socketSize_*paddingScale,
        socketSize_/2.0f*paddingScale
    );
    return boundRect;
}

SocketGraphic::SocketType SocketGraphic::getIO() { return type_; }


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
