#include "Gui/Network/TabMenu.h"
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <qapplication.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qwidget.h>
#include <QEvent>

enzo::ui::TabMenu::TabMenu(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    std::cout << "ctor\n";
    searchBar_ = new QLineEdit("hello world");
    auto box = new QVBoxLayout(this);
    box->addWidget(searchBar_);

    // searchBar_->setFocusPolicy(Qt::NoFocus);
    setDisabled(true);
}

void enzo::ui::TabMenu::showOnMouse(float dx, float dy)
{
    // searchBar_->setFocusPolicy(Qt::StrongFocus);
    setDisabled(false);
    std::cout << "showing\n";
    QPoint cursorPos = mapToParent(mapFromGlobal(QCursor::pos()));
    std::cout << "tab menu pos: " << cursorPos.x() << " " << cursorPos.y() << "\n";
    move(cursorPos + QPoint(dx, dy));
    show();
    setFocus();
    raise();
}

void enzo::ui::TabMenu::focusOutEvent(QFocusEvent *event)
{
    std::cout << "focus lost\n";
    QWidget::focusOutEvent(event); 
    setDisabled(true);
    // searchBar_->setFocusPolicy(Qt::NoFocus);
    hide();
}

bool enzo::ui::TabMenu::event(QEvent *event)
{
    std::cout << "event\n";
    if(
        (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        && event->spontaneous()
    )
    {
        auto *clone = static_cast<QKeyEvent *>(event)->clone();

        if(event->type() == QEvent::KeyPress)
        {
            if(static_cast<QKeyEvent*>(event)->key()==Qt::Key_Tab)
            {
                     
                focusOutEvent(static_cast<QFocusEvent*>(event));
                return true;
            }
            std::cout << "key pressed: " << static_cast<QKeyEvent*>(event)->text().toStdString() << "\n";
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            std::cout << "key release: " << static_cast<QKeyEvent*>(event)->text().toStdString() << "\n";
        }
        QApplication::sendEvent(searchBar_, clone);
        return true;
    }
    return QWidget::event(event);

}

