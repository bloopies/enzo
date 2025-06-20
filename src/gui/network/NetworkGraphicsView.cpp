#include "gui/network/NetworkGraphicsView.h"
#include <QGraphicsItem>
#include "gui/network/NetworkGraphicsScene.h"
#include <iostream>
#include <QMouseEvent>
#include <QScrollBar>

NetworkGraphicsView::NetworkGraphicsView(QWidget *parent, QGraphicsScene* scene)
: QGraphicsView(parent) 
{
    setScene(scene);

    initUI();


}

void NetworkGraphicsView::initUI()
{
    // zoom from mouse
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // disable scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    //
    setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);
}


void NetworkGraphicsView::mousePressEvent(QMouseEvent *event)
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

void NetworkGraphicsView::mouseMoveEvent(QMouseEvent *mouseEvent)
{

    if( mouseEvent->buttons() & Qt::MiddleButton)
    {
        QPointF pos = mouseEvent->pos();
        QPointF delta = pos-panStartPos;
        std::cout << "pos: " << mouseEvent->pos().x() << " " << mouseEvent->pos().y() << "\n";
        std::cout << "delta: " << delta.x() << " " << delta.y() << "\n";

        float speed = 1.0f;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        panStartPos = mouseEvent->pos();
        mouseEvent->accept();
        return;
    }

    QGraphicsView::mouseMoveEvent(mouseEvent);
    
}

void NetworkGraphicsView::wheelEvent(QWheelEvent *event)
{
    std::cout << "delta: " << event->angleDelta().x() << "\n";
    std::cout << "delta: " << event->angleDelta().y() << "\n";
    int delta = event->angleDelta().y();
    if(delta > 0)
    {
        scale(1.1, 1.1);
    }
    else if(delta < 0)
    {
        scale(0.9, 0.9);
    }
    event->accept();
}

