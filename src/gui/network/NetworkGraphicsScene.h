#pragma once

#include <QGraphicsScene>

class NetworkGraphicsScene
: public QGraphicsScene
{
public:
    NetworkGraphicsScene(QGraphicsView *parent = nullptr);
private:
    QGraphicsView* parent_;
protected:
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

};
