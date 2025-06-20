#include "gui/network/NodeGraphic.h"

NodeGraphic::NodeGraphic(QGraphicsItem *parent)
{
    title_ = new QGraphicsTextItem(this);
    title_->setPlainText("hello world!");
    setFlag(QGraphicsItem::ItemIsMovable);
}

