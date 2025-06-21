#include "gui/network/NodeEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>

NodeEdgeGraphic::NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent)
: QGraphicsItem(parent), socket1_{socket1}, socket2_{socket2}
{
    setZValue(-1);
}

QRectF NodeEdgeGraphic::boundingRect() const
{
    auto boundRect = QRect(10,10,10,10);
    return boundRect;
}

void NodeEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen("white"));
    painter->drawLine(socket1_->scenePos(),socket2_->scenePos());
 
}


