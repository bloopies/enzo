#pragma once

#include <QGraphicsScene>

class NetworkGraphicsScene
: public QGraphicsScene
{
public:
    NetworkGraphicsScene();
private:
    uint sceneWidth_;
    uint sceneHeight_;
protected:
};
