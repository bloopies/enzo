#include "Gui/Parameters/AbstractFormParm.h"
#include "Gui/Parameters/AbstractSliderParm.h"
#include <qboxlayout.h>
#include <QLabel>
#include <iostream>


enzo::ui::AbstractFormParm::AbstractFormParm(std::weak_ptr<prm::Parameter> parameter)
: parameter_{parameter}
{
    if(auto sharedParameter=parameter_.lock())
    {
        std::string name = sharedParameter->getName();
        auto label = new QLabel(QString::fromStdString(name+":"));
        label->setStyleSheet("QLabel{background: none}");
        label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

        auto slider = new AbstractSliderParm();
        connect(slider, &AbstractSliderParm::valueChanged, this, &AbstractFormParm::changeValue); 
        slider->setValue(sharedParameter->evalFloat());

        mainLayout_ = new QHBoxLayout();
        mainLayout_->addWidget(label);
        mainLayout_->addWidget(slider);
        mainLayout_->setContentsMargins(0,0,0,0);

        setFixedHeight(24);
        setProperty("class", "Parameter");
        setStyleSheet(".Parameter { background-color: none;}");
        setLayout(mainLayout_);
    }

}

void enzo::ui::AbstractFormParm::changeValue(enzo::bt::floatT value)
{
    if(auto sharedParameter=parameter_.lock())
    {
        sharedParameter->setFloat(value);
    }
    else
    {
        std::cout << "ERROR: parameter no longer exists\n";

    }
     
}
