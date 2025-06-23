#include "gui/network/SocketGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>
#include "gui/network/NodeEdgeGraphic.h"

SocketGraphic::SocketGraphic(SocketGraphic::SocketType type, QGraphicsItem *parent)
: QGraphicsItem(parent), type_{type}
{
    brushActive_ = QBrush("white");
    brushInactive_ = QBrush("#9f9f9f");
    socketSize_ = 3;
    setAcceptHoverEvents(true);
    initBoundingBox();
}

void SocketGraphic::addEdge(NodeEdgeGraphic* edge)
{
    std::cout << "adding edge\n";
    edges_.insert(edge);
}

void SocketGraphic::removeEdge(NodeEdgeGraphic* edge)
{
    std::cout << "removing edge\n";
    std::cout << "before size: " << edges_.size() << "\n";
    edges_.erase(edge);
    std::cout << "after size: " << edges_.size() << "\n";
    // auto it = find(edges_.begin(), edges_.end(), edge);
    // if(it!=edges_.end())
    // {
    //     edges_.erase(it);
    // }
}

void SocketGraphic::initBoundingBox()
{
    boundRect_ = QRect(
        -socketSize_/2.0f*paddingScale_, 
        -socketSize_/2.0f*paddingScale_,
        socketSize_*paddingScale_,
        socketSize_*paddingScale_
    );
    
}

void SocketGraphic::posChanged(QPointF pos)
{
    std::cout << "socket pos changed\n";
    // 
    for(auto* edge : edges_)
    {
        // edge->setPos(startSocket_->scenePos(), socket->scenePos());
        if(type_==SocketType::Input)
        {
            edge->setStartPos(this->scenePos());
        }
        else if(type_==SocketType::Output)
        {
            edge->setEndPos(this->scenePos());
        }
    }
}



QRectF SocketGraphic::boundingRect() const
{
    return boundRect_;
}

QPainterPath SocketGraphic::shape() const{
    QPainterPath path;
    QPointF startPt(boundRect_.center().x(), type_==SocketType::Input ? boundRect_.top() : boundRect_.bottom());
    path.moveTo(startPt);
    path.arcTo(boundRect_, 0, type_==SocketType::Input ? 180 : -180);
    path.lineTo(boundRect_.right(), boundRect_.center().y());
    path.closeSubpath();

    return path;
}

SocketGraphic::SocketType SocketGraphic::getIO() { return type_; }


void SocketGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(hovered_ ? brushActive_ : brushInactive_);
    painter->drawEllipse(QPoint(0,0), socketSize_, socketSize_);

    // painter->drawRect(boundRect_);

 
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
