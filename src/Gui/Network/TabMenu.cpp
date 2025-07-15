#include "Gui/Network/TabMenu.h"
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <qapplication.h>
#include <qlineedit.h>
#include <qwidget.h>
#include <QEvent>

enzo::ui::TabMenu::TabMenu(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    setFocusPolicy(Qt::StrongFocus);
    searchBar_ = new QLineEdit("hello world");
    auto box = new QVBoxLayout(this);
    box->addWidget(searchBar_);
}

void enzo::ui::TabMenu::showOnMouse(float dx, float dy)
{
    QPoint cursorPos = mapFromGlobal(QCursor::pos());
    std::cout << "inside" << cursorPos.x() << " " << cursorPos.y() << "\n";
    move(cursorPos + QPoint(dx, dy));
    show();
    setFocus();
}

void enzo::ui::TabMenu::focusOutEvent(QFocusEvent *event)
{
    std::cout << "focus lost\n";
    QWidget::focusOutEvent(event); 
    close();
}

bool enzo::ui::TabMenu::event(QEvent *event)
{
    if(
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::KeyRelease
    )
    {
        QApplication::postEvent(searchBar_, event->clone());
        return true;
    }
    return QWidget::event(event);

}

// void enzo::ui::TabMenu::keyPressEvent(QKeyEvent *event)
// {
//     searchBar_->keyPressEvent(event);
// }
// void enzo::ui::TabMenu::keyReleaseEvent(QKeyEvent *event)
// {
// }
