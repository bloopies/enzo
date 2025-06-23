#include "gui/network/NodeGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>
#include <stdexcept>
#include <string>
#include "gui/network/DisplayFlagButton.h"
#include "gui/network/SocketGraphic.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

NodeGraphic::NodeGraphic(QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    maxTitleLen_ = 10;
    socketSize_ = 3;
    title_ = "hello world";
    bodyRect_ = QRect(-10, -10, 10*maxTitleLen_, 20);

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    initSockets();
    initFlagButtons();
}

void NodeGraphic::initFlagButtons()
{
    displayFlagButton_ = new DisplayFlagButton(this);
    float padding = 4;
    displayFlagButton_->setPos(QPointF(bodyRect_.right()-displayFlagButton_->getWidth()/2.0f-padding, bodyRect_.center().y()));
}

void NodeGraphic::initSockets()
{
    auto* socketInput = new SocketGraphic(SocketGraphic::SocketType::Input, this);
    socketInput->setPos(getSocketPosition(0, SocketGraphic::SocketType::Input));
    inputs_.push_back(socketInput);

    auto* socketOutput = new SocketGraphic(SocketGraphic::SocketType::Output, this);
    socketOutput->setPos(getSocketPosition(0, SocketGraphic::SocketType::Output));
    outputs_.push_back(socketOutput);
}

// void setInputEdge(NodeEdgeGraphic* edge, int indx)
// {

// }

// void setOutputEdge(NodeEdgeGraphic* edge, int indx)
// {

// }


// void NodeGraphic::addEdge(NodeEdgeGraphic* edge)
// {
//     edges_.push_back(edge);
// }

SocketGraphic* NodeGraphic::getInput(int indx) const
{
    if(inputs_.size()==0)
    {
        throw std::out_of_range("Can't access inputs when node has no inputs: " + std::to_string(indx)); 
    }
    else if(indx>inputs_.size()-1)
    {
        throw std::out_of_range("Can't access input: " + std::to_string(indx)); 
    }
    return inputs_.at(indx);
}
SocketGraphic* NodeGraphic::getOutput(int indx) const
{
    if(outputs_.size()==0)
    {
        throw std::out_of_range("Can't access outputs when node has no outputs: " + std::to_string(indx)); 
    }
    else if(indx>inputs_.size()-1)
    {
        throw std::out_of_range("Can't access input: " + std::to_string(indx)); 
    }
    return outputs_.at(indx);
}

QRectF NodeGraphic::boundingRect() const
{
    QRectF boundRect = bodyRect_;
    float padding = 0;
    boundRect.adjust(-padding, -padding, padding, padding);
    return boundRect;
}

void NodeGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush whiteBrush = QBrush("white");
    QPen greenPen = QPen(Qt::green);
    greenPen.setWidth(6);
    if(isSelected()) painter->setPen(QPen(QColor("#edd044")));
    else painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor("#1b1b1b")));

    painter->drawRoundedRect(bodyRect_, 5, 5);

    painter->setPen(QPen(QColor("white")));
    painter->drawText(	bodyRect_, Qt::AlignCenter, title_.c_str());
 
}

void NodeGraphic::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    updatePositions(event->scenePos());
}

// void NodeGraphic::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// {
//     updatePositions(event->scenePos());
//     QGraphicsItem::mouseReleaseEvent(event);
// }

void NodeGraphic::updatePositions(QPointF pos)
{
    // NOTE: in the future I might store socket ids as internal member variables,
    // but for now I'm just going based on order
    for(int socketIndex=0; socketIndex<inputs_.size(); ++socketIndex)
    {
        inputs_[socketIndex]->posChanged(getSocketScenePosition(socketIndex, SocketGraphic::SocketType::Input));
    }
    for(int socketIndex=0; socketIndex<outputs_.size(); ++socketIndex)
    {
        outputs_[socketIndex]->posChanged(getSocketScenePosition(socketIndex, SocketGraphic::SocketType::Output));
    }
}

QPointF NodeGraphic::getSocketPosition(int socketIndex, SocketGraphic::SocketType socketType)
{
    float xPos, yPos;
    xPos = bodyRect_.center().x();
    yPos = socketType == SocketGraphic::SocketType::Input ? bodyRect_.top() : bodyRect_.bottom();

    return QPointF(xPos, yPos);
}
QPointF NodeGraphic::getSocketScenePosition(int socketIndex, SocketGraphic::SocketType socketType)
{
    return this->pos()+getSocketPosition(socketIndex, socketType);
}


// QVariant NodeGraphic::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
// {
//     if (change == ItemPositionChange && scene()) {
//         for(auto socket : inputs_)
//         {
//             socket->posChanged(value.toPointF());
//         }
//         for(auto socket : outputs_)
//         {
//             socket->posChanged(value.toPointF());
//         }
//     };

//     return QGraphicsItem::itemChange(change, value);
// }
