#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetPanel.h"
#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetMenuBar.h"
#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"
#include <QTableWidget>
#include <QTreeWidget>
#include <QLabel>
#include <qframe.h>
#include <qtablewidget.h>
#include <QPainterPath>

GeometrySpreadsheetPanel::GeometrySpreadsheetPanel(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_ = new QVBoxLayout();


    auto *t = new QTreeView(parent);
    t->setRootIsDecorated(false);
    t->setAlternatingRowColors(true);
    t->setStyleSheet(R"(
        QTreeView {
            background-color: #282828;
            alternate-background-color: #242424;
            paint-alternating-row-colors-for-empty-area: 1;
        }
    )");
    t->setFrameStyle(QFrame::NoFrame);
    
    auto model = new GeometrySpreadsheetModel({"hello", "world"});
    t->setModel(model);


    mainLayout_->addWidget(new GeometrySpreadsheetMenuBar());
    mainLayout_->addWidget(t);

    setLayout(mainLayout_);
}

void GeometrySpreadsheetPanel::resizeEvent(QResizeEvent *event)
{
    QPainterPath path;
    constexpr float radius = 10;
    path.addRoundedRect(mainLayout_->contentsRect(), radius, radius);
    QRegion region = QRegion(path.toFillPolygon().toPolygon());
    this->setMask(region);
}

