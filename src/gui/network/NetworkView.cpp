#include "gui/network/NetworkView.h"
#include <QGraphicsItem>
#include "gui/network/NetworkGraphicsScene.h"
#include <iostream>
#include <QMouseEvent>
#include <QScrollBar>

NetworkView::NetworkView(QWidget *parent)
: QGraphicsView(parent) 
{
    QGraphicsScene *scene = new NetworkGraphicsScene(this);
    setScene(scene);

    QPen greenPen = QPen(Qt::green);
    greenPen.setWidth(6);


    auto* rect1 = scene->addRect(50, 50, 100, 100, greenPen);
    rect1->setFlag(QGraphicsItem::ItemIsMovable);

    auto* rect2 = scene->addRect(80, 120, 100, 100, greenPen);
    rect2->setFlag(QGraphicsItem::ItemIsMovable);

}


void NetworkView::mousePressEvent(QMouseEvent *event)
{
    if(
        event->button() & Qt::MiddleButton
    )
    {
        panStartPos = event->pos();
        event->accept();
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

// void NetworkView::mouseReleaseEvent(QMouseEvent *event)
// {
//     if(
//         event->button() & Qt::MiddleButton
//     )
//     {
//         panStartPos = QPointF(0,0);
//     }
// }

void NetworkView::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    if( mouseEvent->buttons() & Qt::MiddleButton)
    {
        QPointF pos = mouseEvent->pos();
        QPointF delta = pos-panStartPos;
        std::cout << "pos: " << mouseEvent->pos().x() << " " << mouseEvent->pos().y() << "\n";
        std::cout << "delta: " << delta.x() << " " << delta.y() << "\n";

        float speed = 1.0f;
        setSceneRect(sceneRect().translated(-delta.x()*speed, -delta.y()*speed));
        panStartPos = mouseEvent->pos();
        mouseEvent->accept();
        return;
    }

    QGraphicsView::mouseMoveEvent(mouseEvent);
    
}

