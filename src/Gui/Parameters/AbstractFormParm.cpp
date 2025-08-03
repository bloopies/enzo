#include "Gui/Parameters/AbstractFormParm.h"
#include "Engine/Types.h"
#include "Gui/Parameters/AbstractSliderParm.h"
#include "Gui/Parameters/StringParm.h"
#include <qboxlayout.h>
#include <QLabel>
#include <iostream>
#include <qlabel.h>
#include <string>


enzo::ui::AbstractFormParm::AbstractFormParm(std::weak_ptr<prm::Parameter> parameter)
: parameter_{parameter}
{
    if(auto sharedParameter=parameter_.lock())
    {
        std::string name = sharedParameter->getName();
        label_ = new QLabel(QString::fromStdString(name+":"));
        label_->setStyleSheet("QLabel{background: none}");
        label_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

        mainLayout_ = new QHBoxLayout();
        mainLayout_->addWidget(label_);
        mainLayout_->setContentsMargins(0,0,0,0);

        switch(sharedParameter->getType())
        {
            case prm::Type::FLOAT:
            {
                AbstractSliderParm* slider;
                slider = new AbstractSliderParm();
                slider->setValue(sharedParameter->evalFloat());
                mainLayout_->addWidget(slider);
                connect(slider, &AbstractSliderParm::valueChanged, this, [this](bt::floatT value){this->changeValue(value, 0);}); 
                break;
            }
            case prm::Type::XYZ:
            {
                AbstractSliderParm* slider1 = new AbstractSliderParm();
                AbstractSliderParm* slider2 = new AbstractSliderParm();
                AbstractSliderParm* slider3 = new AbstractSliderParm();
                slider1->setValue(sharedParameter->evalFloat());
                QHBoxLayout* vectorLayout = new QHBoxLayout();
                vectorLayout->addWidget(slider1);
                vectorLayout->addWidget(slider2);
                vectorLayout->addWidget(slider3);
                mainLayout_->addLayout(vectorLayout);
                connect(slider1, &AbstractSliderParm::valueChanged, this, [this](bt::floatT value){this->changeValue(value, 0);}); 
                connect(slider2, &AbstractSliderParm::valueChanged, this, [this](bt::floatT value){this->changeValue(value, 1);}); 
                connect(slider3, &AbstractSliderParm::valueChanged, this, [this](bt::floatT value){this->changeValue(value, 2);}); 
                break;
            }
            case prm::Type::STRING:
            {
                StringParm* stringParm = new StringParm();

                connect(stringParm, &StringParm::valueChanged, this, [this](bt::String value){this->changeValue(value, 0);}); 

                mainLayout_->addWidget(stringParm);

                break;


            }
            default:
                throw std::runtime_error("Parameter panel: paremeter type not accounted for " + std::to_string(static_cast<int>(sharedParameter->getType())));

        }




        setFixedHeight(24);
        setProperty("class", "Parameter");
        setStyleSheet(".Parameter { background-color: none;}");
        setLayout(mainLayout_);

    }

}

int enzo::ui::AbstractFormParm::getLeftPadding()
{

    return label_->minimumSizeHint().width();
}

void enzo::ui::AbstractFormParm::setLeftPadding(int padding)
{
    label_->setFixedWidth(padding);
}



void enzo::ui::AbstractFormParm::changeValue(enzo::bt::floatT value, unsigned int index)
{
    if(auto sharedParameter=parameter_.lock())
    {
        sharedParameter->setFloat(value, index);
    }
    else
    {
        std::cout << "ERROR: parameter no longer exists\n";

    }
     
}

void enzo::ui::AbstractFormParm::changeValue(enzo::bt::String value, unsigned int index)
{
    if(auto sharedParameter=parameter_.lock())
    {
        sharedParameter->setString(value, index);
    }
    else
    {
        std::cout << "ERROR: parameter no longer exists\n";

    }
     
}


