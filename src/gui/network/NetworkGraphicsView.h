#pragma once
#include <qgraphicsitem.h>
#include <qwidget.h>
#include <QGraphicsView>
#include <QGraphicsScene>

class Network;

class NetworkGraphicsView
: public QGraphicsView
{
public:
    NetworkGraphicsView(QWidget *parent = nullptr, Network* network=nullptr, QGraphicsScene* scene = nullptr);
private:
    QPointF panStartPos;
    void initUI();
    QGraphicsScene* scene_;
    Network* network_;

protected:
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leftMousePress(QMouseEvent *event);
    QGraphicsItem* getItemAtClick(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;

};
