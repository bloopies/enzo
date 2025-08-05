#pragma once

#include <QWidget>
#include <QVBoxLayout>

class GeometrySpreadsheetPanel
: public QWidget
{
public:
    GeometrySpreadsheetPanel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public Q_SLOTS:
    void selectionChanged();
private:
    QVBoxLayout* mainLayout_;
    QWidget* bgWidget_;
protected:
    void resizeEvent(QResizeEvent *event) override;


};
