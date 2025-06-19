#include "gui/network/NetworkGraphicsScene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <iostream>
#include <qgraphicsview.h>

NetworkGraphicsScene::NetworkGraphicsScene(QGraphicsView *parent)
: QGraphicsScene() 
{
    parent_ = parent;
}

void NetworkGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    std::cout << "delta: " << wheelEvent->delta() << "\n";
    int delta = wheelEvent->delta();
    if(delta > 0)
    {
        parent_->scale(1.1, 1.1);
    }
    else if(delta < 0)
    {
        parent_->scale(0.9, 0.9);
    }
    wheelEvent->accept();
}


