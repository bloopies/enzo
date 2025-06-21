#pragma once
#include <QWidget>
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/SocketGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"

class Network
: public QWidget
{
public:
    Network(QWidget* parent = nullptr);
    void socketClicked(SocketGraphic* socket);
    void mouseMoved(QMouseEvent *event);
private:
    QLayout* mainLayout_;
    NetworkGraphicsScene* scene_;
    NetworkGraphicsView* view_;
    FloatingEdgeGraphic* floatingEdge_=nullptr;
    void keyPressEvent(QKeyEvent *event) override;

protected:
};
