#include "Gui/Network/TabMenu.h"
#include "Engine/Operator/OperatorTable.h"
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <qapplication.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qwidget.h>
#include <QEvent>
#include <QPainterPath>
#include <QPushButton>
#include <string>

enzo::ui::TabMenu::TabMenu(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    setAttribute(Qt::WA_TranslucentBackground);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    mainLayout_ = new QVBoxLayout(this);
    setLayout(mainLayout_);

    searchBar_ = new QLineEdit();
    searchBar_->setFocusPolicy(Qt::NoFocus);
    nodeHolder_ = new QWidget();
    nodeScrollArea_ = new QScrollArea();

    nodeScrollArea_->setWidget(nodeHolder_);
    nodeScrollArea_->setWidgetResizable(true);

    mainLayout_->addWidget(searchBar_);
    mainLayout_->addWidget(nodeScrollArea_);

    nodeHolderLayout_ = new QVBoxLayout();
    nodeHolder_->setLayout(nodeHolderLayout_);
    auto tableItems = enzo::op::OperatorTable::getData();
    nodeScrollArea_->setFocusPolicy(Qt::NoFocus);
    for(auto tableItem : tableItems)
    {
        auto button = new QPushButton(tableItem.displayName.c_str());
        button->setFocusPolicy(Qt::NoFocus);
        button->setStyleSheet(R"(
            QPushButton {
                background-color: #181c1d;
                border: none;
                padding: 0px;
                border-radius: 4px;
            }

            QPushButton:hover {
                background-color: #d0d0d0;
                color: black;
            }

            QPushButton:pressed {
                background-color: #b0b0b0;
            }
        )");
        nodeHolderLayout_->addWidget(button);
    }

    setDisabled(true);
}

void enzo::ui::TabMenu::showOnMouse(float dx, float dy)
{
    setDisabled(false);
    std::cout << "showing\n";
    QPoint cursorPos = mapToParent(mapFromGlobal(QCursor::pos()));
    std::cout << "tab menu pos: " << cursorPos.x() << " " << cursorPos.y() << "\n";
    searchBar_->clear();
    move(cursorPos + QPoint(dx, dy));
    show();
    adjustSize();
    setFocus();
    raise();
}

void enzo::ui::TabMenu::focusOutEvent(QFocusEvent *event)
{
    std::cout << "focus lost\n";
    QWidget::focusOutEvent(event); 
    setDisabled(true);
    hide();
}

bool enzo::ui::TabMenu::event(QEvent *event)
{
    if(
        (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        && event->spontaneous()
    )
    {
        auto *clone = static_cast<QKeyEvent *>(event)->clone();

        if(event->type() == QEvent::KeyPress)
        {
            auto key = static_cast<QKeyEvent*>(event)->key();
            if(key==Qt::Key_Tab || key==Qt::Key_Escape)
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

// void enzo::ui::TabMenu::resizeEvent(QResizeEvent *event)
// {
//     QPainterPath path;
//     constexpr float radius = 10;
//     path.addRoundedRect(contentsRect(), radius, radius);
//     QRegion region = QRegion(path.toFillPolygon().toPolygon());
//     this->setMask(region);
// }
