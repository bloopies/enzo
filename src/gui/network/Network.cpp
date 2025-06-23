#include "gui/network/Network.h"
#include "gui/network/DisplayFlagButton.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/NodeGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"
#include "gui/network/SocketGraphic.h"
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

    NodeGraphic* node4 = new NodeGraphic();
    node4->setPos(50, -200);
    scene_->addItem(node4);

    // scene_->addItem(new NodeEdgeGraphic(node1->getOutput(0), node2->getInput(0)));

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

void Network::deleteEdge(QGraphicsItem* edge)
{
    std::cout << "----\ndeleting edge\n";
    if(!edge) return;
    if(prevHoverItem_==edge)
    {
        prevHoverItem_=nullptr;
    }
    // scene_->removeItem(edge);
    // scene_->update();
    // view_->update();
    // NOTE: deleting edge kept giving me segmentation faults
    // I coundn't figure it out so I'm just leaving it for now
    delete edge;
    std::cout << "finished deleting edge\n----\n";
}

void Network::mousePressEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton)
    {
        leftMousePressed(event);
    }

}

void Network::leftMousePressed(QMouseEvent *event)
{
    std::cout << "LEFT MOUSE PRESSED\n";
    Qt::KeyboardModifiers mods = event->modifiers();

    // QGraphicsItem* itemClicked = view_->itemAt(event->pos());
    QList<QGraphicsItem*> clickedItems = view_->items(event->pos());
    QGraphicsItem* clickedSocket = itemOfType<SocketGraphic>(clickedItems);
    QGraphicsItem* clickedEdge = itemOfType<NodeEdgeGraphic>(clickedItems);


    // delete edges
    if(mods & Qt::ControlModifier && clickedEdge)
    {
        deleteEdge(clickedEdge);
    }
    // socket logic
    else if(clickedSocket)
    {
        socketClicked(static_cast<SocketGraphic*>(clickedSocket), event);
    }
    // floating edge
    else if(floatingEdge_)
    {
        destroyFloatingEdge();
    }
    // display flag
    else if(QGraphicsItem* clickedDisplayFlag = itemOfType<DisplayFlagButton>(clickedItems))
    {
        std::cout << "HERE\n";
        static_cast<DisplayFlagButton*>(clickedDisplayFlag)->setEnabled(true);
    }

}




void Network::socketClicked(SocketGraphic* socket, QMouseEvent *event)
{
    std::cout << "socket clicked\n";
    // if first click
    if(!floatingEdge_)
    {
        startSocket_=socket;
        std::cout << "creating floating edge\n";
        floatingEdge_ = new FloatingEdgeGraphic(socket);
        scene_->addItem(floatingEdge_);
        floatingEdge_->setFloatPos(view_->mapToScene(event->pos()));
    }
    // second click
    // connect to opposite type
    else if (socket->getIO()!=startSocket_->getIO())
    {
        auto inputSocket = startSocket_->getIO()==SocketGraphic::SocketType::Input ? startSocket_ : socket;
        auto outputSocket = socket->getIO()==SocketGraphic::SocketType::Output ? socket : startSocket_;

        NodeEdgeGraphic* newEdge = new NodeEdgeGraphic(inputSocket, outputSocket);

        newEdge->setPos(inputSocket->scenePos(), outputSocket->scenePos());
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

    QList<QGraphicsItem*> hoverItems = view_->items(event->pos());
    // QGraphicsItem* hoverItem = view_->itemAt(event->pos());
    QGraphicsItem* hoverEdge = itemOfType<NodeEdgeGraphic>(hoverItems);

    // set node edge color
    if(ctrlMod && hoverEdge)
    {
        if(event->buttons() & Qt::LeftButton)
        {
            deleteEdge(hoverEdge);
        }
        else
        {
            std::cout << "highlighting\n";
            highlightEdge(hoverEdge, true);
        }
    }
    // reset node edge color
    if(
        prevHoverItem &&
        (!ctrlMod || hoverEdge!=prevHoverItem)
    )
    {
        std::cout << "unhighlighting\n";
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

    QList<QGraphicsItem*> hoverItems = view_->items(widgetPos);

    // edge detection
    if(
        event->key() == Qt::Key_Control
    )
    {
        QGraphicsItem* hoverItem = itemOfType<NodeEdgeGraphic>(hoverItems);
        if(hoverItem!=nullptr)
        {
            highlightEdge(hoverItem, true);
        }

    }

    if(event->key() == Qt::Key_Escape)
    {
        destroyFloatingEdge();
    }
}

void Network::highlightEdge(QGraphicsItem* edge, bool state)
{
    if(!edge || !isType<NodeEdgeGraphic>(edge)) return;
    if(state)
    {
        static_cast<NodeEdgeGraphic*>(edge)->setColor(QColor("red"));
        prevHoverItem_=edge;
        // NOTE: sloppy fix for color not updating
        view_->update();
    }
    else
    {
        static_cast<NodeEdgeGraphic*>(edge)->useDefaultColor();
        // NOTE: sloppy fix for color not updating
        view_->update();
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

void Network::mouseReleaseEvent(QMouseEvent *event)
{
    // std::cout << "----\nMOUSE RELEASED\n---\n";
    QList<QGraphicsItem*> hoverItems = view_->items(event->pos());
    QGraphicsItem* hoverSocket = itemOfType<SocketGraphic>(hoverItems);
    if(floatingEdge_ && hoverSocket)
    {
        socketClicked(static_cast<SocketGraphic*>(hoverSocket), event);
    }
}
