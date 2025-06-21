#pragma once
#include <QWidget>
#include <qgraphicsitem.h>
#include <typeinfo>
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/SocketGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"

class Network
: public QWidget
{
public:
    Network(QWidget* parent = nullptr);
    void socketClicked(SocketGraphic* socket, QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void leftMousePress(QMouseEvent *event);
private:
    QLayout* mainLayout_;
    NetworkGraphicsScene* scene_;
    NetworkGraphicsView* view_;

    FloatingEdgeGraphic* floatingEdge_=nullptr;
    SocketGraphic* startSocket_=nullptr;

    QGraphicsItem* prevHoverItem_=nullptr;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void destroyFloatingEdge();

    void highlightEdge(QGraphicsItem* edge, bool state);

    template<typename T>
    bool isType(QGraphicsItem* item)
    {
        return item && typeid(*item)==typeid(T);
    }

protected:
    void resizeEvent(QResizeEvent *event) override;
};
