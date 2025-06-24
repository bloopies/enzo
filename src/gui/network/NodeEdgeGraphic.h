#pragma once
#include <QGraphicsItem>
#include "gui/network/SocketGraphic.h"

#include <QPainter>

class NodeEdgeGraphic
: public QGraphicsItem
{
public:
    NodeEdgeGraphic(SocketGraphic* socket1, SocketGraphic* socket2, QGraphicsItem *parent = nullptr);
    ~NodeEdgeGraphic();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPainterPath shape() const override;
    // void setColor(QColor color);
    // void useDefaultColor();
    void updateDeleteHighlightPen();
    void setPos(QPointF pos1, QPointF pos2);
    void setStartPos(QPointF pos);
    void setEndPos(QPointF pos);
    void cleanUp();
    void setDeleteHighlight(bool enable);
    QPen deleteHighlightPen_;
    QPen defaultPen_;

    bool deleteHighlight_=false;

private:
    SocketGraphic* socket1_;
    SocketGraphic* socket2_;
    QColor color_;
    QColor defaultColor_;
    QPointF pos1_;
    QPointF pos2_;
    QPainterPath path_;
    QRectF boundRect_;
    qreal padding_=40;

    void updatePath();
};

