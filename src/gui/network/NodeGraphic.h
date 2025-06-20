#pragma once
#include <QGraphicsItem>
#include <QPainter>

class NodeGraphic
: public QGraphicsItem
{
public:
    NodeGraphic(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override
    {
        qreal penWidth = 6;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                      20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QPen greenPen = QPen(Qt::green);
        greenPen.setWidth(6);
        painter->setPen(greenPen);

        painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
    }

private:
    QGraphicsTextItem* title_;
};

