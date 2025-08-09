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


    view_ = new QTreeView(parent);
    view_->setRootIsDecorated(false);
    view_->setAlternatingRowColors(true);
    view_->setStyleSheet(R"(
        QTreeView {
            background-color: #282828;
            alternate-background-color: #242424;
            paint-alternating-row-colors-for-empty-area: 1;
        }
    )");
    view_->setFrameStyle(QFrame::NoFrame);
    
    model_ = new GeometrySpreadsheetModel({"hello", "world"});
    view_->setModel(model_);


    mainLayout_->addWidget(new GeometrySpreadsheetMenuBar());
    mainLayout_->addWidget(view_);

    setLayout(mainLayout_);
}

void GeometrySpreadsheetPanel::selectionChanged(enzo::nt::OpId opId)
{
    model_->selectionChanged(opId);
    view_->update();
}

void GeometrySpreadsheetPanel::resizeEvent(QResizeEvent *event)
{
    QPainterPath path;
    constexpr float radius = 10;
    path.addRoundedRect(mainLayout_->contentsRect(), radius, radius);
    QRegion region = QRegion(path.toFillPolygon().toPolygon());
    this->setMask(region);
}

