#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <qtreeview.h>
#include "Engine/Types.h"
#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"

class GeometrySpreadsheetPanel
: public QWidget
{
public:
    GeometrySpreadsheetPanel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public Q_SLOTS:
    void geometryChanged(enzo::geo::Geometry& geometry);
private:
    QVBoxLayout* mainLayout_;
    QWidget* bgWidget_;
    GeometrySpreadsheetModel* model_;
    QTreeView* view_;
protected:
    void resizeEvent(QResizeEvent *event) override;


};
