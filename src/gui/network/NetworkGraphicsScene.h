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
    uint gridSize_;
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};
