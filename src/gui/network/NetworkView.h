#pragma once
#include <qwidget.h>
#include <QGraphicsView>

class NetworkView
: public QGraphicsView
{
public:
    NetworkView(QWidget *parent = nullptr);
private:
    QPointF panStartPos;

protected:
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    void mousePressEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;

};
