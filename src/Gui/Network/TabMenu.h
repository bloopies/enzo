#pragma once

#include <qlineedit.h>
#include <qwidget.h>
#include <QVBoxLayout>

namespace enzo::ui
{
class TabMenu
: public QWidget
{
public:
    TabMenu(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void showOnMouse(float dx=0, float dy=0);
     
private:
    QLineEdit* searchBar_;
protected:
    void focusOutEvent(QFocusEvent *event) override;
    bool event(QEvent *event) override;
    // void keyPressEvent(QKeyEvent *event) override;
    // void keyReleaseEvent(QKeyEvent *event) override;
};
}
