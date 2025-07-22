#include "Gui/ParametersPanel/ParametersPanel.h"
#include "Gui/Parameters/AbstractSliderParm.h"
#include "Gui/Parameters/AbstractFormParm.h"
#include "Gui/Parameters/FloatParm.h"
#include <qboxlayout.h>
#include <QSpinBox>
#include <qnamespace.h>
#include <qwidget.h>
#include <QLineEdit>

ParametersPanel::ParametersPanel(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_ = new QVBoxLayout();
    parametersLayout_ = new QVBoxLayout();
    parametersLayout_->setAlignment(Qt::AlignTop);
    bgWidget_ = new QWidget();
    bgWidget_->setLayout(parametersLayout_);

    bgWidget_->setObjectName("ParametersPanelBg");
    bgWidget_->setStyleSheet(R"(
           QWidget#ParametersPanelBg {
                background-color: #282828;
               border-radius: 10px;
           }
    )"
      );

    mainLayout_->addLayout(parametersLayout_);
    mainLayout_->addWidget(bgWidget_);

    // parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());
    // parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());
    // parametersLayout_->addWidget(new enzo::ui::FloatParm());
    // parametersLayout_->addWidget(new enzo::ui::FloatParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractFormParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractFormParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractFormParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractFormParm());


    setLayout(mainLayout_);
}
