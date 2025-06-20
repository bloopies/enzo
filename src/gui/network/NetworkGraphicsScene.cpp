#include "gui/network/NetworkGraphicsScene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneWheelEvent>
#include <iostream>
#include <qgraphicsview.h>

NetworkGraphicsScene::NetworkGraphicsScene()
: QGraphicsScene() 
{
    sceneWidth_ = 64000;
    sceneHeight_ = 64000;

    setSceneRect(sceneWidth_/-2.0f, sceneHeight_/-2.0f, sceneWidth_, sceneHeight_);
    
}

