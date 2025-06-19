#include "gui/NetworkView.h"
#include <QGraphicsItem>
#include <iostream>

NetworkView::NetworkView(QWidget *parent)
: QGraphicsView(parent) 
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    QPen greenPen = QPen(Qt::green);
    greenPen.setWidth(6);


    auto* rect1 = scene->addRect(50, 50, 100, 100, greenPen);
    rect1->setFlag(QGraphicsItem::ItemIsMovable);

}

