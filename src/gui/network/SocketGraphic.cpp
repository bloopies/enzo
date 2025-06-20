#include "gui/network/SocketGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>

SocketGraphic::SocketGraphic(QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    socketSize_ = 3;
}

QRectF SocketGraphic::boundingRect() const
{
    auto boundRect = QRect(-socketSize_/2, -socketSize_/2, socketSize_, socketSize_);
    return boundRect;
}

void SocketGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush whiteBrush = QBrush("white");
    painter->setPen(Qt::NoPen);
    painter->setBrush(whiteBrush);
    painter->drawEllipse(QPoint(0,0), socketSize_, socketSize_);
 
}


