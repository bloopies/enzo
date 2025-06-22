#include "gui/network/NodeEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>

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
    socket1_->removeEdge(this);
    socket2_->removeEdge(this);
}


QRectF NodeEdgeGraphic::boundingRect() const
{
    // std::cout << "bounds set" << socket1_->scenePos().x() << " " << socket1_->scenePos().y() << " " << socket2_->scenePos().x() << " " << socket2_->scenePos().y() << "\n";
    auto boundRect = QRectF(socket1_->scenePos(), socket2_->scenePos());
    return boundRect;
}

QPainterPath NodeEdgeGraphic::shape() const{
    // FIX: shape not changing with node position
    QPainterPath path;
    // std::cout << "setting shape to: " << socket1_->scenePos().x() << " " << socket2_->scenePos().x() <<"\n";
    path.moveTo(socket1_->scenePos());
    path.lineTo(socket2_->scenePos());

    QPainterPathStroker stroker;
    stroker.setWidth(10);
    return stroker.createStroke(path);
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
    std::cout << "painting\n";
    pen_.setCapStyle(Qt::RoundCap);
    painter->setPen(pen_);
    painter->drawLine(socket1_->scenePos(),socket2_->scenePos());
 
}


