#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetMenuBar.h"
#include <QLabel>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <QButtonGroup>
#include <QPainter>
#include <QPaintEvent>
#include <icecream.hpp>

GeoSheetModeButton::GeoSheetModeButton(QWidget* parent)
: QPushButton(parent)
{
    setFixedSize(QSize(23,23));
    setObjectName("GeoSheetModeButton");
    setCheckable(true);
    // setStyleSheet(
    // R"(
    //     #GeoSheetModeButton
    //     {
    //         background: transparent;
    //         border: none;
    //     }
    //     #GeoSheetModeButton::checked
    //     {
    //         opacity: 50;
    //         border: none;
    //     }
    // )");

    setIcon(QIcon(":/node-icons/grid.svg"));
}

void GeoSheetModeButton::enterEvent(QEnterEvent *event)
{
    hovered_=true;
    QPushButton::enterEvent(event);

}

void GeoSheetModeButton::leaveEvent(QEvent *event)
{
    hovered_=false;
    QPushButton::leaveEvent(event);
}

void GeoSheetModeButton::paintEvent(QPaintEvent* event)
{
    const QIcon buttonIcon = icon();

    if(!buttonIcon.isNull())
    {
        QPainter painter(this);

        QSize size = iconSize();

        if(!isChecked())
        {
            painter.setOpacity(0.5);
        }
        if(hovered_)
        {
            size*=1.1;
        }



        QPixmap pixmap = buttonIcon.pixmap(size);
        QPoint center = event->rect().center() - QPoint(size.width() / 2, size.height() / 2);
        // QPoint center = QPoint(0,0);
        painter.drawPixmap(center, pixmap);

    }

}


GeoSheetMenuBarModeSelection::GeoSheetMenuBarModeSelection(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_ = new QHBoxLayout();
    QWidget* buttonBg = new QWidget();
    buttonBg->setObjectName("GeoSheetMenuBarButtonBg");
    buttonBg->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    constexpr int bgSizeMargin = 5;
    buttonBg->setContentsMargins(bgSizeMargin,0,bgSizeMargin,0);
    buttonBg->setStyleSheet(
    R"(
        #GeoSheetMenuBarButtonBg
        {
            background-color: #383838;
            border-radius: 8px;
        }

    )");
    QHBoxLayout* buttonBgLayout = new QHBoxLayout();
    constexpr int margin = 0;
    buttonBgLayout->setContentsMargins(margin,margin,margin,margin);

    modeButtonGroup_.setExclusive(true);

    auto newButton = [this, &buttonBgLayout]()
    {
        auto newButton = new GeoSheetModeButton();
        modeButtonGroup_.addButton(newButton);
        buttonBgLayout->addWidget(newButton);
        return newButton;
    };

    auto pointButton = newButton();
    auto vertButton = newButton();
    auto primButton = newButton();
    auto globalButton = newButton();

    pointButton->setChecked(true);

    buttonBg->setLayout(buttonBgLayout);

    mainLayout_->addWidget(buttonBg);

    setLayout(mainLayout_);
}

GeometrySpreadsheetMenuBar::GeometrySpreadsheetMenuBar(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_ = new QHBoxLayout();
    mainLayout_->addWidget(new QLabel("Node: testGeometryRat"));
    mainLayout_->addWidget(new GeoSheetMenuBarModeSelection());

    setLayout(mainLayout_);
}
