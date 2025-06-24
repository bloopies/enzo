#include "gui/network/NodeEdgeGraphic.h"
#include <QTextDocument>
#include "gui/network/SocketGraphic.h"
#include <iostream>
#include <qgraphicsitem.h>
#include <QGraphicsScene>

NodeEdgeGraphic::NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent)
: QGraphicsItem(parent), socket1_{socket1}, socket2_{socket2}, defaultColor_{QColor("white")}
{
    setZValue(-1);
    color_=defaultColor_;
    defaultPen_=QPen(defaultColor_);
    defaultPen_.setCapStyle(Qt::RoundCap);

    deleteHighlightPen_.setCapStyle(Qt::RoundCap);
    deleteHighlightPen_.setWidth(1);
    updateDeleteHighlightPen();


    socket1_->addEdge(this);
    socket2_->addEdge(this);
}

void NodeEdgeGraphic::updateDeleteHighlightPen()
{
    QLinearGradient gradient(pos1_, pos2_);
    gradient.setColorAt(0.0, QColor(255, 0, 0, 200));
    gradient.setColorAt(0.5, QColor(255, 0, 0, 50));
    gradient.setColorAt(1.0, QColor(255, 0, 0, 200));

    deleteHighlightPen_.setBrush(QBrush(gradient));
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
    updateDeleteHighlightPen();
    update();

}

void NodeEdgeGraphic::setPos(QPointF pos1, QPointF pos2)
{
    prepareGeometryChange();
    pos1_ = pos1;
    pos2_ = pos2;
    updatePath();
}

void NodeEdgeGraphic::setDeleteHighlight(bool enable)
{
    deleteHighlight_=enable;
    update();
}

void NodeEdgeGraphic::setStartPos(QPointF pos)
{
    prepareGeometryChange();
    pos1_ = pos;
    updatePath();
}

void NodeEdgeGraphic::setEndPos(QPointF pos)
{
    prepareGeometryChange();
    pos2_ = pos;
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

// void NodeEdgeGraphic::setColor(QColor color)
// {
//     std::cout << "color set to: " << color.name().toStdString() << "\n";
//     color_ = color;
//     pen_.setColor(color_);
//     update();
// }

// void NodeEdgeGraphic::useDefaultColor()
// {
//     setColor(defaultColor_);
// }

void NodeEdgeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // std::cout << "painting\n";
    painter->setPen(deleteHighlight_ ? deleteHighlightPen_ : defaultPen_);
    painter->drawPath(path_);
 
}

void NodeEdgeGraphic::cleanUp()
{
    // these probably aren't necessary but i'm trying to fix a bug
    prepareGeometryChange();
    update();
    scene()->update();

    scene()->removeItem(this);
    socket1_->removeEdge(this);
    socket2_->removeEdge(this);
}
