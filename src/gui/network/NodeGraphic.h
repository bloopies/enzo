#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include "Engine/Types.h"
#include "gui/network/DisplayFlagButton.h"
#include "gui/network/SocketGraphic.h"
#include "gui/network/NodeIconGraphic.h"
#include "gui/network/NodeEdgeGraphic.h"
#include <iostream>

class NodeGraphic
: public QGraphicsItem
{
public:
    NodeGraphic(enzo::nt::OpId id, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    
    SocketGraphic* getInput(int indx) const;
    SocketGraphic* getOutput(int indx) const;
    QPointF getSocketPosition(int socketIndex, enzo::nt::SocketIOType socketType);
    QPointF getSocketScenePosition(int socketIndex, enzo::nt::SocketIOType socketType);
    QRectF getBodyRect();

    // void addEdge(NodeEdgeGraphic* edge);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // void setInputEdge(NodeEdgeGraphic* edge, int indx);
    // void setOutputEdge(NodeEdgeGraphic* edge, int indx);




private:
    void initSockets();
    void initFlagButtons();
    void initIcon();
    void initFonts();

    enzo::nt::OpId opId_;
    std::vector<SocketGraphic*> inputs_;
    std::vector<SocketGraphic*> outputs_;

    // std::vector<NodeEdgeGraphic*> edges_;

    std::string titleText_="";
    std::string subTitleText_="";
    int maxTitleLen_=10;
    QRectF bodyRect_;
    int socketSize_ = 1;
    int inputSocketCnt_=0;
    int outputSocketCnt_=0;
    NodeIconGraphic* icon_;
    int iconScale_;
    float iconPadding_ = 5;
    QGraphicsItem* test_;

    QFont titleFont_;
    QFont subTitleFont_;
    int titlePadding_;

    QRectF titleRect_;
    QRectF subTitleRect_;

    DisplayFlagButton* displayFlagButton_;

    void updatePositions();
protected:
        QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;
        // void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

