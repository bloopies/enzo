#include "gui/network/Network.h"
#include "Engine/Operator/GeometryConnection.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include "gui/network/DisplayFlagButton.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/NodeGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"
#include "gui/network/SocketGraphic.h"
#include "Engine/Network/NetworkManager.h"
#include <memory>
#include <qboxlayout.h>
#include <QPushButton>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <QLine>

using namespace enzo;

Network::Network(QWidget* parent)
: QWidget(parent)
{

    mainLayout_ = new QVBoxLayout(parent);
    // mainLayout_->setContentsMargins(0,0,0,0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    this->setLayout(mainLayout_); 


    scene_ = new NetworkGraphicsScene();
    view_ = new NetworkGraphicsView(this, this, scene_);
    nm_ = enzo::nt::NetworkManager::getInstance();


    mainLayout_->addWidget(view_);

}

void Network::resizeEvent(QResizeEvent *event)
{
    QPainterPath path;
    constexpr float radius = 10;
    path.addRoundedRect(mainLayout_->contentsRect(), radius, radius);
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
    // delete edge;
    static_cast<NodeEdgeGraphic*>(edge)->cleanUp();
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
    leftMouseStart = event->pos();

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
        // find closest socket
        clickedSocket = closestItemOfType<SocketGraphic>(clickedItems, view_->mapToScene(event->pos()));
        if(clickedSocket)
        {
            socketClicked(static_cast<SocketGraphic*>(clickedSocket), event);
        }
    }
    // floating edge
    else if(floatingEdge_)
    {
        destroyFloatingEdge();
    }
    else if(QGraphicsItem* clickedNode = itemOfType<NodeGraphic>(clickedItems))
    {
        nodeMoveDelta_=clickedNode->pos()-view_->mapToScene(event->pos());
        std::cout << "move delta: " << nodeMoveDelta_.x() << " " << nodeMoveDelta_.y() << "\n";
        state_=State::MOVING_NODE;
        moveNodeBuffer.clear();
        moveNodeBuffer.push_back(clickedNode);
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
    else if (
        socket->getIO()!=startSocket_->getIO() &&
        startSocket_->getOpId()!=socket->getOpId()
    )
    {

        // order sockets in relation to data flow
        // the input node is the node the data flows from
        auto inputNodeSocket = socket->getIO()==enzo::nt::SocketIOType::Output ? socket : startSocket_;
        // the output node is the node the data flows to
        auto outputNodeSocket = startSocket_->getIO()==enzo::nt::SocketIOType::Input ? startSocket_ : socket;

        std::cout << "CONNECTING opid: " << inputNodeSocket->getOpId() << " -> " << outputNodeSocket->getOpId() << "\n";


        nt::connectOperators(inputNodeSocket->getOpId(), inputNodeSocket->getIndex(), outputNodeSocket->getOpId(), outputNodeSocket->getIndex());


        NodeEdgeGraphic* newEdge = new NodeEdgeGraphic(outputNodeSocket, inputNodeSocket);

        newEdge->setPos(outputNodeSocket->scenePos(), inputNodeSocket->scenePos());
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

    QList<QGraphicsItem*> hoverItems = view_->items(event->pos());

    if(state_==State::MOVING_NODE)
    {
        moveNodes(view_->mapToScene(event->pos())+nodeMoveDelta_);
        return;
    }

    if(floatingEdge_)
    {
        if(
            SocketGraphic* hoverSocket = static_cast<SocketGraphic*>(closestItemOfType<SocketGraphic>(hoverItems, view_->mapToScene(event->pos())));
            hoverSocket &&
            hoverSocket!=startSocket_ &&
            hoverSocket->getIO()!=startSocket_->getIO() &&
            hoverSocket->getOpId()!=startSocket_->getOpId()
            
        )
        {
            floatingEdge_->setFloatPos(hoverSocket->scenePos());
        }
        else
        {
            floatingEdge_->setFloatPos(view_->mapToScene(event->pos()));
        }
        event->accept();
        return;
    }

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

void Network::moveNodes(QPointF pos)
{

    for(auto node : moveNodeBuffer)
    {
        node->setPos(pos);
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
    QPointF viewPos = view_->mapToScene(widgetPos);
    

    QList<QGraphicsItem*> hoverItems = view_->items(widgetPos);

    // edge detection
    switch(event->key())
    {

        case( Qt::Key_Control):
        {
            QGraphicsItem* hoverItem = itemOfType<NodeEdgeGraphic>(hoverItems);
            if(hoverItem!=nullptr)
            {
                highlightEdge(hoverItem, true);
            }
            break;
        }
        case(Qt::Key_Escape):
        {
            destroyFloatingEdge();
            break;
        }
        case(Qt::Key_Tab):
        {
            if(auto newNode = createNode())
            {
                newNode->setPos(viewPos);
            }

            break;
        }
    }
}

NodeGraphic* Network::createNode()
{
    if(nt::OpId id = nm_->addOperator())
    {
        NodeGraphic* newNode = new NodeGraphic(id);
        scene_->addItem(newNode);
        nodeStore_.emplace(id, newNode);
        
        return newNode;
    }
    else
    {
        return nullptr;
    }
}


void Network::highlightEdge(QGraphicsItem* edge, bool state)
{
    if(!edge || !isType<NodeEdgeGraphic>(edge)) return;
    if(state)
    {
        static_cast<NodeEdgeGraphic*>(edge)->setDeleteHighlight(true);
        prevHoverItem_=edge;
        // NOTE: sloppy fix for color not updating
        view_->update();
    }
    else
    {
        static_cast<NodeEdgeGraphic*>(edge)->setDeleteHighlight(false);
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
    if(event->button() == Qt::LeftButton)
    {
        // display flag
        if(
            QGraphicsItem* clickedDisplayFlag = itemOfType<DisplayFlagButton>(hoverItems);
            clickedDisplayFlag &&
            QLineF(event->pos(), leftMouseStart).length()<5.0f
        )
        {
            NodeGraphic* clickedNode = static_cast<NodeGraphic*>(itemOfType<NodeGraphic>(hoverItems));
            enzo::nt::OpId opId = clickedNode->getOpId();
            if(auto prevDisplayOpId = nm_->getDisplayOp(); prevDisplayOpId)
            {
                NodeGraphic* prevDisplayNode = nodeStore_.at(*prevDisplayOpId);
                prevDisplayNode->setDisplayFlag(false);
            }
            nm_->setDisplayOp(opId);
            static_cast<DisplayFlagButton*>(clickedDisplayFlag)->setEnabled(true);
        }
        if(state_==State::MOVING_NODE)
        {
            moveNodeBuffer.clear();
            state_=State::DEFAULT;
        }
        else if(floatingEdge_ && hoverSocket)
        {
            hoverSocket = closestItemOfType<SocketGraphic>(hoverItems, view_->mapToScene(event->pos()));
            if(hoverSocket)
            {
                socketClicked(static_cast<SocketGraphic*>(hoverSocket), event);
            }
        }
    }
}
