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
    float paddingScale = 20;
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
