#pragma once
#include <QGraphicsItem>
#include <QPainter>

class SocketGraphic
: public QGraphicsItem
{
public:
    SocketGraphic(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int socketSize_ = 1;
};

