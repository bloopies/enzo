#include "Gui/ParametersPanel/ParametersPanel.h"
#include "Gui/Parameters/AbstractSliderParm.h"
#include <qboxlayout.h>
#include <QSpinBox>
#include <qwidget.h>
#include <QLineEdit>

ParametersPanel::ParametersPanel(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
    mainLayout_ = new QVBoxLayout();
    parametersLayout_ = new QVBoxLayout();
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

    parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());
    parametersLayout_->addWidget(new enzo::ui::AbstractSliderParm());


    setLayout(mainLayout_);
}
