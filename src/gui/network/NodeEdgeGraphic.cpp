#include "gui/network/NodeEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>
#include <QGraphicsScene>

NodeEdgeGraphic::NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent)
: QGraphicsItem(parent), socket1_{socket1}, socket2_{socket2}, defaultColor_{QColor("white")}, pen_{QPen(QColor("white"))}
{
    setZValue(-1);
    color_=defaultColor_;

    socket1_->addEdge(this);
    socket2_->addEdge(this);
}

NodeEdgeGraphic::~NodeEdgeGraphic()
{
    std::cout << "edge destructor\n";
    cleanUp();
    std::cout << "destructor finished\n";
}

void NodeEdgeGraphic::updatePath()
{
    qreal cubicStrength = 40;
    path_.clear();
    path_.moveTo(pos1_);
    path_.cubicTo(pos1_-QPoint(0,cubicStrength), pos2_+QPoint(0,cubicStrength), pos2_);
    update();

}

void NodeEdgeGraphic::setPos(QPointF pos1, QPointF pos2)
{
    pos1_ = pos1;
    pos2_ = pos2;
    prepareGeometryChange();
    updatePath();
}

void NodeEdgeGraphic::setStartPos(QPointF pos)
{
    pos1_ = pos;
    prepareGeometryChange();
    updatePath();
}

void NodeEdgeGraphic::setEndPos(QPointF pos)
{
    pos2_ = pos;
    prepareGeometryChange();
    updatePath();
}

QRectF NodeEdgeGraphic::boundingRect() const
{
    // std::cout << "bounds set" << socket1_->scenePos().x() << " " << socket1_->scenePos().y() << " " << socket2_->scenePos().x() << " " << socket2_->scenePos().y() << "\n";
    // QRectF boundRect_ = QRectF(socket1_->scenePos(), socket1_->scenePos()).normalized();
    QRectF boundRect_ = QRectF(pos1_, pos2_).normalized();
    boundRect_.adjust(-padding_,-padding_,padding_,padding_);
    return boundRect_;
}

QPainterPath NodeEdgeGraphic::shape() const{
    // FIX: shape not changing with node position
    std::cout << "setting shape to: " << socket1_->scenePos().x() << " " << socket2_->scenePos().x() <<"\n";

    QPainterPathStroker stroker;
    stroker.setWidth(padding_);
    return stroker.createStroke(path_);
}

void NodeEdgeGraphic::setColor(QColor color)
{
    std::cout << "color set to: " << color.name().toStdString() << "\n";
    color_ = color;
    pen_.setColor(color_);
    update();
}

void NodeEdgeGraphic::useDefaultColor()
{
    setColor(defaultColor_);
}

void NodeEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // std::cout << "painting\n";
    pen_.setCapStyle(Qt::RoundCap);
    painter->setPen(pen_);
    painter->drawPath(path_);
 
}

void NodeEdgeGraphic::cleanUp()
{
    scene()->removeItem(this);
    socket1_->removeEdge(this);
    socket2_->removeEdge(this);
}
