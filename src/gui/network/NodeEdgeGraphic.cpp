#include "gui/network/NodeEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>

NodeEdgeGraphic::NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent)
: QGraphicsItem(parent), socket1_{socket1}, socket2_{socket2}, defaultColor_{QColor("white")}
{
    setZValue(-1);
    color_=defaultColor_;
}

QRectF NodeEdgeGraphic::boundingRect() const
{
    auto boundRect = QRectF(socket1_->scenePos(), socket2_->scenePos());
    return boundRect;
}

QPainterPath NodeEdgeGraphic::shape() const{
    QPainterPath path;
    path.moveTo(socket1_->scenePos());
    path.lineTo(socket2_->scenePos());

    QPainterPathStroker stroker;
    stroker.setWidth(10);
    return stroker.createStroke(path);
}

void NodeEdgeGraphic::setColor(QColor color)
{
    color_ = color;
}

void NodeEdgeGraphic::useDefaultColor()
{
    setColor(defaultColor_);
}

void NodeEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto pen = QPen(color_);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->drawLine(socket1_->scenePos(),socket2_->scenePos());
 
}


