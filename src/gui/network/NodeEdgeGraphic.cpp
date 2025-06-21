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
    auto boundRect = QRectF(socket1_->scenePos(), socket2_->scenePos());
    return boundRect;
}

void NodeEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto pen = QPen("white");
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->drawLine(socket1_->scenePos(),socket2_->scenePos());
 
}


