#include "gui/network/Network.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include <qboxlayout.h>
#include <QPushButton>

Network::Network(QWidget* parent)
{

    mainLayout_ = new QVBoxLayout(parent);
    mainLayout_->setContentsMargins(0,0,0,0);

    this->setLayout(mainLayout_); 


    NetworkGraphicsScene* scene = new NetworkGraphicsScene();
    NetworkGraphicsView* view = new NetworkGraphicsView(parent, scene);
    
    mainLayout_->addWidget(view);
}
