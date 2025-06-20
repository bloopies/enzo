#include "gui/network/Network.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/NodeGraphic.h"
#include <qboxlayout.h>
#include <QPushButton>
#include <QGraphicsItem>

Network::Network(QWidget* parent)
{

    mainLayout_ = new QVBoxLayout(parent);
    mainLayout_->setContentsMargins(0,0,0,0);

    this->setLayout(mainLayout_); 


    NetworkGraphicsScene* scene = new NetworkGraphicsScene();
    NetworkGraphicsView* view = new NetworkGraphicsView(parent, scene);

    QPen greenPen = QPen(Qt::green);
    greenPen.setWidth(6);

    auto* rect1 = scene->addRect(50, 50, 100, 100, greenPen);
    rect1->setFlag(QGraphicsItem::ItemIsMovable);

    auto* rect2 = scene->addRect(80, 120, 100, 100, greenPen);
    rect2->setFlag(QGraphicsItem::ItemIsMovable);

    auto* rect3 = scene->addRect(80, -120, 100, 100, greenPen);
    rect3->setFlag(QGraphicsItem::ItemIsMovable);

    NodeGraphic* node1 = new NodeGraphic();
    scene->addItem(node1);
    
    mainLayout_->addWidget(view);
}
