#pragma once
#include <QGraphicsItem>

class DisplayFlagButton
: public QGraphicsItem
{
public:
    DisplayFlagButton(QGraphicsItem *parent = nullptr);
    float getWidth();
private:
    QRectF baseRect_;
    QColor disabledColor_=QColor("#373737");
    QColor enabledColor_=QColor("#00BFFF");
protected:
    QRectF boundingRect() const override;    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};
