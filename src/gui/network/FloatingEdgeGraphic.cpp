#include "gui/network/FloatingEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>

FloatingEdgeGraphic::FloatingEdgeGraphic(SocketGraphic* socket1, QGraphicsItem *parent)
: QGraphicsItem(parent), socket1_{socket1}
{
    floatPos_ = socket1_->scenePos();
    setZValue(-1);
}

QRectF FloatingEdgeGraphic::boundingRect() const
{
    auto boundRect = QRectF(socket1_->scenePos(), floatPos_).normalized();
    return boundRect;
}

void FloatingEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // auto pen = QPen("white");

    QLinearGradient gradient(socket1_->scenePos(), floatPos_);
    gradient.setColorAt(0.0, QColor(255, 255, 255, 255));
    gradient.setColorAt(1.0, QColor(255, 255, 255, 50));

    QPen pen(QBrush(gradient), 1);

    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->drawLine(socket1_->scenePos(),floatPos_);
 
}

void FloatingEdgeGraphic::setFloatPos(QPointF floatPos) {
    prepareGeometryChange();
    floatPos_ = floatPos;
    update();
}

