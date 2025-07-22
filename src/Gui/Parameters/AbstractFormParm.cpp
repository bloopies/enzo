#include "Gui/Parameters/AbstractFormParm.h"
#include "Gui/Parameters/AbstractSliderParm.h"
#include <qboxlayout.h>
#include <QLabel>


enzo::ui::AbstractFormParm::AbstractFormParm()
{
    auto label = new QLabel("Parm name:");
    label->setStyleSheet("QLabel{background: none}");
    label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

    mainLayout_ = new QHBoxLayout();
    mainLayout_->addWidget(label);
    mainLayout_->addWidget(new AbstractSliderParm());
    mainLayout_->setContentsMargins(0,0,0,0);

    setFixedHeight(24);
    setProperty("class", "Parameter");
    setStyleSheet(".Parameter { background-color: none;}");
    setLayout(mainLayout_);
}

