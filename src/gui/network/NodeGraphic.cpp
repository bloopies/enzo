#include "gui/network/NodeGraphic.h"
#include <QTextDocument>
#include <iostream>
#include <qgraphicsitem.h>
#include <stdexcept>
#include <string>
#include "gui/network/SocketGraphic.h"

NodeGraphic::NodeGraphic(QGraphicsItem *parent)
: QGraphicsItem(parent)
{
    maxTitleLen_ = 10;
    socketSize_ = 3;
    title_ = "hello world";
    bodyRect_ = QRect(-10, -10, 10*maxTitleLen_, 20);

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    initSockets();
}

void NodeGraphic::initSockets()
{
    auto* socketInput = new SocketGraphic(SocketGraphic::SocketType::Input, this);
    socketInput->setPos(bodyRect_.center().x(), bodyRect_.top());
    inputs_.push_back(socketInput);

    auto* socketOutput = new SocketGraphic(SocketGraphic::SocketType::Output, this);
    socketOutput->setPos(bodyRect_.center().x(), bodyRect_.bottom());
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
    float padding = 10;
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


