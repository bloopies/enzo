#include "gui/network/Network.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/NodeGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"
#include <qboxlayout.h>
#include <QPushButton>
#include <QGraphicsItem>
#include <QMouseEvent>

Network::Network(QWidget* parent)
: QWidget(parent)
{

    mainLayout_ = new QVBoxLayout(parent);
    mainLayout_->setContentsMargins(0,0,0,0);

    this->setLayout(mainLayout_); 


    scene_ = new NetworkGraphicsScene();
    view_ = new NetworkGraphicsView(this, this, scene_);

    QPen greenPen = QPen(Qt::green);
    greenPen.setWidth(6);

    auto* rect1 = scene_->addRect(50, 50, 100, 100, greenPen);
    rect1->setFlag(QGraphicsItem::ItemIsMovable);

    auto* rect2 = scene_->addRect(80, 120, 100, 100, greenPen);
    rect2->setFlag(QGraphicsItem::ItemIsMovable);

    auto* rect3 = scene_->addRect(80, -120, 100, 100, greenPen);
    rect3->setFlag(QGraphicsItem::ItemIsMovable);

    NodeGraphic* node1 = new NodeGraphic();
    node1->setPos(-50, -50);
    scene_->addItem(node1);
    
    NodeGraphic* node2 = new NodeGraphic();
    node2->setPos(50, 50);
    scene_->addItem(node2);

    NodeEdgeGraphic* edge1 = new NodeEdgeGraphic(node1->getOutput(0), node2->getInput(0));
    scene_->addItem(edge1);

    node1->addEdge(edge1);
    node2->addEdge(edge1);



    mainLayout_->addWidget(view_);
}

void Network::socketClicked(SocketGraphic* socket)
{
    std::cout << "socket clicked\n";
    if(!floatingEdge_)
    {
        std::cout << "creating floating edge\n";
        floatingEdge_ = new FloatingEdgeGraphic(socket);
        scene_->addItem(floatingEdge_);
    }
}


void Network::mouseMoved(QMouseEvent *event)
{
    if(floatingEdge_)
    {
        floatingEdge_->setFloatPos(view_->mapToScene(event->pos()));
        floatingEdge_->update();
    }
}

