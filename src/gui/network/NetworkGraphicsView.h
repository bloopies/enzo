#pragma once
#include <qwidget.h>
#include <QGraphicsView>
#include <QGraphicsScene>

class NetworkGraphicsView
: public QGraphicsView
{
public:
    NetworkGraphicsView(QWidget *parent = nullptr, QGraphicsScene* scene = nullptr);
private:
    QPointF panStartPos;
    void initUI();

protected:
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;

};
