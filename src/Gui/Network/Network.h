#pragma once
#include <QWidget>
#include <iterator>
#include <memory>
#include <qgraphicsitem.h>
#include <qpoint.h>
#include <typeinfo>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Types.h"
#include "Gui/Network/NetworkGraphicsView.h"
#include "Gui/Network/NodeEdgeGraphic.h"
#include "Gui/Network/NetworkGraphicsScene.h"
#include "Gui/Network/NodeGraphic.h"
#include "Gui/Network/SocketGraphic.h"
#include "Gui/Network/FloatingEdgeGraphic.h"
#include <iostream>
#include <QPointer>
#include <unordered_map>

class Network
: public QWidget
{
public:
    Network(QWidget* parent = nullptr);
    void socketClicked(SocketGraphic* socket, QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    QSize sizeHint() const override { return QSize(-1, -1); }

    enum class State
    {
        DEFAULT,
        MOVING_NODE
    };

private:
    QLayout* mainLayout_;
    NetworkGraphicsScene* scene_;
    NetworkGraphicsView* view_;

    std::unordered_map<enzo::nt::OpId, NodeGraphic*> nodeStore_;

    FloatingEdgeGraphic* floatingEdge_=nullptr;
    SocketGraphic* startSocket_=nullptr;

    QGraphicsItem* prevHoverItem_=nullptr;
    // nodes currently being moved
    std::vector<QGraphicsItem*> moveNodeBuffer;
    QPointF nodeMoveDelta_;

    State state_=State::DEFAULT;
    QPointF leftMouseStart;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void destroyFloatingEdge();
    void deleteEdge(QGraphicsItem* edge);

    NodeGraphic* createNode(enzo::nt::opConstructor ctorFunc);

    void highlightEdge(QGraphicsItem* edge, bool state);
    void leftMousePressed(QMouseEvent* event);

    void moveNodes(QPointF pos);

    template<typename T>
    bool isType(QGraphicsItem* item)
    {
        return item && typeid(*item)==typeid(T);
    }

    template<typename T>
    QGraphicsItem* itemOfType(QList<QGraphicsItem*> items)
    {
        for(QGraphicsItem* item : items)
        {
            if(item && typeid(*item)==typeid(T))
            {
                return item;
            }
        }
        return nullptr;
    }

    template<typename T>
    QGraphicsItem* closestItemOfType(QList<QGraphicsItem*> items, QPointF centerPos)
    {
        std::vector <QGraphicsItem*> filteredItems;
        for(QGraphicsItem* item : items)
        {
            if(item && typeid(*item)==typeid(T))
            {
                filteredItems.push_back(item);
            }
        }

        if(filteredItems.size()==0) return nullptr;
        if(filteredItems.size()==1) return filteredItems.at(0);

        QGraphicsItem* closestItem=filteredItems.at(0);
        float closestDist=QLineF(closestItem->scenePos(), centerPos).length();

        for(size_t i=1; i<filteredItems.size(); ++i)
        {
            QGraphicsItem* item = filteredItems.at(i);
            auto currentDist = QLineF(item->scenePos(), centerPos).length();
            if(currentDist < closestDist)
            {
                closestItem = item;
                closestDist = currentDist;
            }

        }

        return closestItem;
    }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
