#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <qbuttongroup.h>
#include <qpushbutton.h>

class GeoSheetModeButton
: public QPushButton
{
public:
    GeoSheetModeButton(QWidget *parent = nullptr);
private:
    QHBoxLayout* mainLayout_;
protected:
    void paintEvent(QPaintEvent *) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    bool hovered_ = false;
};

class GeometrySpreadsheetMenuBar
: public QWidget
{
public:
    GeometrySpreadsheetMenuBar(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private:
    QHBoxLayout* mainLayout_;
};

class GeoSheetMenuBarModeSelection
: public QWidget
{
public:
    GeoSheetMenuBarModeSelection(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private:
    QHBoxLayout* mainLayout_;
    QButtonGroup modeButtonGroup_;
};
