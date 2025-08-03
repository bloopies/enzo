#include "Gui/Parameters/StringParm.h"
#include "Engine/Types.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <iostream>
#include <qboxlayout.h>
#include <qnamespace.h>
#include <algorithm>
#include <QLineEdit>
#include <string>


enzo::ui::StringParm::StringParm(bt::String value, QWidget *parent)
: QLineEdit(parent)
{
    // tells qt to style the widget even though it's a Q_OBJECT
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(24);

    value_ = value;
    setText(QString::fromStdString(value_));
    

    // setAlignment(Qt::AlignCenter);
    // setStyleSheet("background-color: none;");
    setProperty("type", "StringParm");
    setStyleSheet(R"(
                  QWidget[type="StringParm"]
                  {
                      border-radius: 6px;
                      border: 1px solid #383838;
                      padding: 0px 5px 0px 5px;
                  }
                  )");

    setText(QString::fromStdString(value_));

    connect(this, &QLineEdit::textEdited, this, &enzo::ui::StringParm::setValueQString);
}

void enzo::ui::StringParm::setValue(bt::String value)
{
    value_ = value;
    setText(QString::fromStdString(value_));

    valueChanged(value_);

}

void enzo::ui::StringParm::setValueQString(QString value)
{
    value_ = value.toStdString();
    valueChanged(value_);
}
