#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <unordered_set>


class NodeEdgeGraphic;

class SocketGraphic
: public QGraphicsItem
{
public:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    enum class SocketType {
        Input,
        Output
    };

    SocketGraphic(SocketGraphic::SocketType type, QGraphicsItem *parent = nullptr);
    SocketType getIO();
    void addEdge(NodeEdgeGraphic* edge);
    void removeEdge(NodeEdgeGraphic* edge);
    void posChanged(QPointF pos);

private:
    int socketSize_ = 1;
    QBrush brushInactive_;
    QBrush brushActive_;
    bool hovered_=false;
    SocketType type_;
    std::unordered_set<NodeEdgeGraphic*> edges_;
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

