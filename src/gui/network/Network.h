#pragma once
#include <QWidget>
#include <memory>
#include <qgraphicsitem.h>
#include <typeinfo>
#include "gui/network/NetworkGraphicsView.h"
#include "gui/network/NodeEdgeGraphic.h"
#include "gui/network/NetworkGraphicsScene.h"
#include "gui/network/SocketGraphic.h"
#include "gui/network/FloatingEdgeGraphic.h"
#include <iostream>
#include <QPointer>

class Network
: public QWidget
{
public:
    Network(QWidget* parent = nullptr);
    void socketClicked(SocketGraphic* socket, QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
private:
    QLayout* mainLayout_;
    NetworkGraphicsScene* scene_;
    NetworkGraphicsView* view_;

    FloatingEdgeGraphic* floatingEdge_=nullptr;
    SocketGraphic* startSocket_=nullptr;

    QGraphicsItem* prevHoverItem_=nullptr;
    // QPointer<QGraphicsItem> prevHoverItem_=nullptr;
    // std::shared_ptr<QGraphicsItem> prevHoverItem_=nullptr;
    // QList<QGraphicsItem*> prevHoverItems_;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void destroyFloatingEdge();
    void deleteEdge(QGraphicsItem* edge);

    void highlightEdge(QGraphicsItem* edge, bool state);
    void leftMousePressed(QMouseEvent* event);

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
