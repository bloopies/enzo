#pragma once

#include <qlineedit.h>
#include <QLabel>
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
    ~TabMenu()
    {
        std::cout << "dtor\n";
    }
    void showOnMouse(float dx=0, float dy=0);
     
private:
    QLineEdit* searchBar_;
protected:
    void focusOutEvent(QFocusEvent *event) override;
    bool event(QEvent *event) override;
};
}
