#pragma once

#include <qlineedit.h>
#include <QLabel>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qwidget.h>
#include <QVBoxLayout>
#include <iostream>

namespace enzo::ui
{
class TabMenu
: public QWidget
{
public:
    TabMenu(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void showOnMouse(float dx=0, float dy=0);
     
private:
    QVBoxLayout* mainLayout_;
    QLineEdit* searchBar_;
    QScrollArea* nodeScrollArea_;
    QWidget* nodeHolder_;
    QVBoxLayout* nodeHolderLayout_;
    void doHide();
protected:
    void focusOutEvent(QFocusEvent *event) override;
    bool event(QEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
protected slots:
    void nodeClicked();
};

class TabMenuButton
: public QPushButton
{
public:
    using QPushButton::QPushButton;
    std::string nodeName;
};
}
