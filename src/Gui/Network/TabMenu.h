#pragma once

#include <qcontainerfwd.h>
#include <qlineedit.h>
#include <QLabel>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qwidget.h>
#include <QVBoxLayout>
#include <QSvgWidget>
#include <iostream>

namespace enzo::ui
{
class TabMenuButton
: public QPushButton
{
public:
    TabMenuButton(const QString &text, QWidget *parent = nullptr);
    std::string nodeName;
    QString getDisplayText() {return displayText_;}
private:
    QHBoxLayout* mainLayout_;
    QLabel* textLabel_;
    QSvgWidget* icon_;
    QString displayText_;

};

class TabMenu
: public QWidget
{
public:
    TabMenu(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void showOnMouse(float dx=0, float dy=0);
     
private:
    QVBoxLayout* mainLayout_;
    QLineEdit* searchBar_;
    QScrollArea* nodeScrollArea_;
    QWidget* nodeHolder_;
    QVBoxLayout* nodeHolderLayout_;
    void doHide();
    void textChanged(const QString &text);
    std::vector<TabMenuButton*> buttons_;
protected:
    void focusOutEvent(QFocusEvent *event) override;
    bool event(QEvent *event) override;
    // void resizeEvent(QResizeEvent *event) override;
protected slots:
    void nodeClicked();
};


// class TabMenuSearch
// : public QLineEdit
// {
//     TabMenuSearch(QWidget *parent = nullptr);

// };

}
