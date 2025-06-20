#pragma once
#include <QGraphicsItem>
#include "gui/network/SocketGraphic.h"

#include <QPainter>

class NodeEdgeGraphic
: public QGraphicsItem
{
public:
    NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    SocketGraphic* socket1_;
    SocketGraphic* socket2_;
};

