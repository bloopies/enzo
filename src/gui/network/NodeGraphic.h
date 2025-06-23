#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include "gui/network/DisplayFlagButton.h"
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
    QPointF getSocketPosition(int socketIndex, SocketGraphic::SocketType socketType);
    QPointF getSocketScenePosition(int socketIndex, SocketGraphic::SocketType socketType);

    // void addEdge(NodeEdgeGraphic* edge);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // void setInputEdge(NodeEdgeGraphic* edge, int indx);
    // void setOutputEdge(NodeEdgeGraphic* edge, int indx);




private:
    void initSockets();
    void initFlagButtons();

    std::vector<SocketGraphic*> inputs_;
    std::vector<SocketGraphic*> outputs_;

    // std::vector<NodeEdgeGraphic*> edges_;

    std::string title_="";
    int maxTitleLen_=10;
    QRectF bodyRect_;
    int socketSize_ = 1;
    int inputSocketCnt_=0;
    int outputSocketCnt_=0;

    DisplayFlagButton* displayFlagButton_;

    void updatePositions(QPointF pos);
protected:
        // QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

