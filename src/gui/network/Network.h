#pragma once
#include <QWidget>
#include <memory>
#include <qgraphicsitem.h>
#include <typeinfo>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Types.h"
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/NodeGraphic.h"
#include "gui/network/SocketGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"
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

    enzo::nt::NetworkManager* nm_;

    std::unordered_map<enzo::nt::OpId, NodeGraphic*> nodeStore_;

    FloatingEdgeGraphic* floatingEdge_=nullptr;
    SocketGraphic* startSocket_=nullptr;

    QGraphicsItem* prevHoverItem_=nullptr;
    // nodes currently being moved
    std::vector<QGraphicsItem*> moveNodeBuffer;
    QPointF nodeMoveDelta_;

    State state_=State::DEFAULT;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void destroyFloatingEdge();
    void deleteEdge(QGraphicsItem* edge);

    NodeGraphic* createNode();

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
        // std::cout << "count: " << items.size() << "\n";
        for(QGraphicsItem* item : items)
        {
            std::cout << "item: " << typeid(*item).name() << "\n";
            if(item && typeid(*item)==typeid(T))
            {
                return item;
            }
        }
        return nullptr;
    }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
