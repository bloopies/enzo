#pragma once
#include <QWidget>

class Network
: public QWidget
{
public:
    Network(QWidget* parent = nullptr);
private:
    QLayout* mainLayout_;
};
