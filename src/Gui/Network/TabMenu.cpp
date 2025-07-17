#include <QStyleOptionFrame>
#include <QGraphicsDropShadowEffect>
#include <QSvgRenderer>
#include <QSvgWidget>
#include "Gui/Network/TabMenu.h"
#include "Engine/Operator/OperatorTable.h"
#include "Gui/Network/Network.h"
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <qapplication.h>
#include <qboxlayout.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qobject.h>
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

    mainLayout_ = new QVBoxLayout(this);

    searchBar_ = new QLineEdit();
    nodeHolder_ = new QWidget();
    nodeScrollArea_ = new QScrollArea();
    nodeHolderLayout_ = new QVBoxLayout();

    auto tableItems = enzo::op::OperatorTable::getData();
    for(auto tableItem : tableItems)
    {
        auto button = new TabMenuButton(tableItem.displayName.c_str());
        button->nodeName = tableItem.internalName;
        button->setFocusPolicy(Qt::NoFocus);
        connect(button, &TabMenuButton::clicked, this, &enzo::ui::TabMenu::nodeClicked);
        button->setStyleSheet(R"(
            QPushButton#TabMenuButton {
                background-color: transparent;
                border: 4px solid transparent;
                padding: 0px;
                margin: 0px;
                border-radius: 8px;
            }

            QPushButton#TabMenuButton:hover {
                background-color: #3d3d3d;
                color: white;
            }

            QPushButton#TabMenuButton:pressed {
                background-color: #b0b0b0;
            }
        )");
        nodeHolderLayout_->addWidget(button);
    }

    setLayout(mainLayout_);

    // set focus policy
    searchBar_->setFocusPolicy(Qt::NoFocus);
    nodeScrollArea_->setFocusPolicy(Qt::NoFocus);

    // disable frames
    searchBar_->setFrame(false);
    nodeScrollArea_->setFrameStyle(QStyleOptionFrame::None);


    mainLayout_->addWidget(searchBar_);
    mainLayout_->addWidget(nodeScrollArea_);

    nodeHolderLayout_->setSpacing(0);
    nodeHolderLayout_->setContentsMargins(2,4,2,4);
    nodeHolder_->setLayout(nodeHolderLayout_);
    nodeHolderLayout_->setAlignment(Qt::AlignTop);

    nodeScrollArea_->setWidget(nodeHolder_);
    nodeScrollArea_->setWidgetResizable(true);
    nodeScrollArea_->setMinimumHeight(250);
    nodeScrollArea_->setMinimumWidth(200);

    //style
    searchBar_->setAlignment(Qt::AlignCenter);
    nodeHolder_->setProperty("shade", "dark");
    nodeHolder_->setObjectName("TabMenuNodeHolder");
    nodeHolder_->setStyleSheet(R"(
           QWidget#TabMenuNodeHolder {
                background-color: transparent;
           }
    )"
    );
    nodeScrollArea_->setObjectName("TabMenuNodeScrollArea");
    nodeScrollArea_->setStyleSheet(R"(
           QWidget#TabMenuNodeScrollArea {
                background-color: #d9161616;
               border-radius: 6px;
           }
    )"
    );
    searchBar_->setObjectName("TabMenuSearch");
    searchBar_->setStyleSheet(R"(
           QWidget#TabMenuSearch {
                background-color: #d9161616;
              padding: 3px;
               border-radius: 4px;
           }
    )"
    );

    // drop shadow
    auto dropShadow_ = new QGraphicsDropShadowEffect();
    dropShadow_->setColor(QColor(0,0,0,80));
    dropShadow_->setBlurRadius(15);
    dropShadow_->setOffset(4);
    setGraphicsEffect(dropShadow_);

    setDisabled(true);
}

void enzo::ui::TabMenu::nodeClicked()
{
    TabMenuButton* buttonClicked = static_cast<TabMenuButton*>(sender());
    static_cast<Network*>(parentWidget())->createNode(op::OperatorTable::getOpConstructor(buttonClicked->nodeName));
    doHide();
}


void enzo::ui::TabMenu::showOnMouse(float dx, float dy)
{
    setDisabled(false);
    std::cout << "showing\n";
    QPoint cursorPos = mapToParent(mapFromGlobal(QCursor::pos()));
    searchBar_->clear();
    move(cursorPos + QPoint(dx, dy));
    show();
    adjustSize();
    setFocus();
    raise();
}

void enzo::ui::TabMenu::doHide()
{
    setDisabled(true);
    hide();
}


void enzo::ui::TabMenu::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event); 
    doHide();
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

enzo::ui::TabMenuButton::TabMenuButton(const QString &text, QWidget *parent)
: QPushButton(parent)
{
    setObjectName("TabMenuButton");


    textLabel_ = new QLabel(text);
    textLabel_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    // textLabel_->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    textLabel_->setStyleSheet("background-color: transparent;");

    icon_ = new QSvgWidget(":/node-icons/grid.svg");
    icon_->renderer()->setAspectRatioMode(Qt::KeepAspectRatio);
    icon_->setStyleSheet("background-color: transparent;");
    icon_->setFixedSize(16, 16);

    mainLayout_ = new QHBoxLayout();

    mainLayout_->addWidget(icon_);
    mainLayout_->addWidget(textLabel_);

    setLayout(mainLayout_);

}


