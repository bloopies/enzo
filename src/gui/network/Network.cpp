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
#include <qgraphicsitem.h>
#include <qnamespace.h>

Network::Network(QWidget* parent)
: QWidget(parent)
{

    mainLayout_ = new QVBoxLayout(parent);
    mainLayout_->setContentsMargins(0,0,0,0);


    this->setLayout(mainLayout_); 


    scene_ = new NetworkGraphicsScene();
    view_ = new NetworkGraphicsView(this, this, scene_);

    // QPen greenPen = QPen(Qt::green);
    // greenPen.setWidth(6);

    // auto* rect1 = scene_->addRect(50, 50, 100, 100, greenPen);
    // rect1->setFlag(QGraphicsItem::ItemIsMovable);

    // auto* rect2 = scene_->addRect(80, 120, 100, 100, greenPen);
    // rect2->setFlag(QGraphicsItem::ItemIsMovable);

    // auto* rect3 = scene_->addRect(80, -120, 100, 100, greenPen);
    // rect3->setFlag(QGraphicsItem::ItemIsMovable);

    NodeGraphic* node1 = new NodeGraphic();
    node1->setPos(-50, -50);
    scene_->addItem(node1);
    
    NodeGraphic* node2 = new NodeGraphic();
    node2->setPos(50, 50);
    scene_->addItem(node2);

    NodeGraphic* node3 = new NodeGraphic();
    node3->setPos(50, 200);
    scene_->addItem(node3);

    NodeEdgeGraphic* edge1 = new NodeEdgeGraphic(node1->getOutput(0), node2->getInput(0));
    scene_->addItem(edge1);

    // node1->addEdge(edge1);
    // node2->addEdge(edge1);



    mainLayout_->addWidget(view_);

}

void Network::resizeEvent(QResizeEvent *event)
{
    QPainterPath path;
    path.addRoundedRect(this->rect(), 15, 15);
    QRegion region = QRegion(path.toFillPolygon().toPolygon());
    this->setMask(region);
}

void Network::leftMousePress(QMouseEvent *event)
{
    Qt::KeyboardModifiers mods = event->modifiers();

    QGraphicsItem* itemClicked = view_->itemAt(event->pos());
    if(isType<SocketGraphic>(itemClicked))
    {
        socketClicked(static_cast<SocketGraphic*>(itemClicked), event);
    }
    else if(floatingEdge_)
    {
        destroyFloatingEdge();
    }
    // delete edges
    else if(mods & Qt::ControlModifier && isType<NodeEdgeGraphic>(itemClicked))
    {
        scene_->removeItem(itemClicked);
    }

}




void Network::socketClicked(SocketGraphic* socket, QMouseEvent *event)
{
    std::cout << "socket clicked\n";
    if(!floatingEdge_)
    {
        startSocket_=socket;
        std::cout << "creating floating edge\n";
        floatingEdge_ = new FloatingEdgeGraphic(socket);
        scene_->addItem(floatingEdge_);
        floatingEdge_->setFloatPos(view_->mapToScene(event->pos()));
    }
    // connect to opposite type
    else if (socket->getIO()!=startSocket_->getIO())
    {
        NodeEdgeGraphic* newEdge = new NodeEdgeGraphic(startSocket_, socket);
        scene_->addItem(newEdge);
        destroyFloatingEdge();
    }
}

void Network::destroyFloatingEdge()
{
    if(floatingEdge_)
    {
        scene_->removeItem(floatingEdge_);
        delete floatingEdge_;
        floatingEdge_=nullptr;
    }
}



void Network::mouseMoved(QMouseEvent *event)
{
    // cache and reset prev hover item
    QGraphicsItem* prevHoverItem=prevHoverItem_;
    prevHoverItem_=nullptr;

    // modifiers
    Qt::KeyboardModifiers mods = event->modifiers();
    bool ctrlMod = mods & Qt::ControlModifier;

    if(floatingEdge_)
    {
        floatingEdge_->setFloatPos(view_->mapToScene(event->pos()));
        event->accept();
        return;
    }

    QGraphicsItem* hoverItem = view_->itemAt(event->pos());

    // set node edge color
    if(ctrlMod && isType<NodeEdgeGraphic>(hoverItem))
    {
        highlightEdge(hoverItem, true);
    }
    // reset node edge color
    if(
        (!ctrlMod || hoverItem!=prevHoverItem) &&
        isType<NodeEdgeGraphic>(prevHoverItem)
    )
    {
        highlightEdge(prevHoverItem, false);
    }

}


void Network::keyPressEvent(QKeyEvent *event)
{
    // modifiers
    Qt::KeyboardModifiers mods = event->modifiers();
    bool ctrlMod = mods & Qt::ControlModifier;

    // get pos
    QPoint globalPos = QCursor::pos();
    QPoint widgetPos = mapFromGlobal(globalPos);

    QGraphicsItem* hoverItem = view_->itemAt(widgetPos);

    // edge detection
    if(
        event->key() == Qt::Key_Control &&
        isType<NodeEdgeGraphic>(hoverItem)
    )
    {
        highlightEdge(hoverItem, true);
    }

    if(event->key() == Qt::Key_Escape)
    {
        destroyFloatingEdge();
    }
}

void Network::highlightEdge(QGraphicsItem* edge, bool state)
{
    if(state)
    {
        static_cast<NodeEdgeGraphic*>(edge)->setColor(QColor("red"));
        edge->update();
        prevHoverItem_=edge;
    }
    else
    {
        static_cast<NodeEdgeGraphic*>(edge)->useDefaultColor();
        edge->update();
    }

}


void Network::keyReleaseEvent(QKeyEvent *event)
{
    // modifiers
    Qt::KeyboardModifiers mods = event->modifiers();
    bool ctrlMod = mods & Qt::ControlModifier;

    // edge detection
    if(
        prevHoverItem_ &&
        event->key() == Qt::Key_Control &&
        isType<NodeEdgeGraphic>(prevHoverItem_)
    )
    {
        highlightEdge(prevHoverItem_, false);
    }
}
