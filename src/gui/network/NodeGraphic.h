#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include "gui/network/SocketGraphic.h"
#include "gui/network/NodeEdgeGraphic.h"
#include <iostream>

class NodeGraphic
: public QGraphicsItem
{
public:
    NodeGraphic(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    
    SocketGraphic* getInput(int indx) const;
    SocketGraphic* getOutput(int indx) const;

    void addEdge(NodeEdgeGraphic* edge);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;




private:
    void initSockets();
    std::vector<SocketGraphic*> inputs_;
    std::vector<SocketGraphic*> outputs_;

    std::vector<NodeEdgeGraphic*> edges_;

    std::string title_="";
    int maxTitleLen_=10;
    QRectF bodyRect_;
    int socketSize_ = 1;
    int inputSocketCnt_=0;
    int outputSocketCnt_=0;
};

