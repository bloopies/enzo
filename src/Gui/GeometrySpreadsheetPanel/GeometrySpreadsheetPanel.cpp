#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetPanel.h"
#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetMenuBar.h"
#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"
#include "Engine/Network/NetworkManager.h"
#include <QTableWidget>
#include <QTreeWidget>
#include <QLabel>
#include <qframe.h>
#include <qpushbutton.h>
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
    
    model_ = new GeometrySpreadsheetModel();
    view_->setModel(model_);

    menuBar_ = new GeometrySpreadsheetMenuBar();
    // connect buttons
    connect(menuBar_->modeSelection->pointButton, &QPushButton::clicked, this, [this](){model_->setOwner(enzo::ga::AttributeOwner::POINT);});
    connect(menuBar_->modeSelection->vertexButton, &QPushButton::clicked, this, [this](){model_->setOwner(enzo::ga::AttributeOwner::VERTEX);});
    connect(menuBar_->modeSelection->primitiveButton, &QPushButton::clicked, this, [this](){model_->setOwner(enzo::ga::AttributeOwner::PRIMITIVE);});
    connect(menuBar_->modeSelection->globalButton, &QPushButton::clicked, this, [this](){model_->setOwner(enzo::ga::AttributeOwner::GLOBAL);});
    // set default
    menuBar_->modeSelection->pointButton->click();


    mainLayout_->addWidget(menuBar_);
    mainLayout_->addWidget(view_);

    setLayout(mainLayout_);
}

void GeometrySpreadsheetPanel::setNode(enzo::nt::OpId opId)
{
    menuBar_->setNode(opId);
}


void GeometrySpreadsheetPanel::geometryChanged(enzo::geo::Geometry& geometry)
{
    model_->geometryChanged(geometry);
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

