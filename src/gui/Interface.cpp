#include "gui/Interface.h"
#include "gui/Viewport.h"
#include "gui/NetworkView.h"
#include <qpushbutton.h>
#include <qsplitter.h>

EnzoUI::EnzoUI()
{
    mainLayout_ = new QVBoxLayout();
    this->setLayout(mainLayout_);

    Viewport* viewport = new Viewport();
    NetworkView* networkView = new NetworkView();

    viewportSplitter_ = new QSplitter();
    viewportSplitLayout_ = new QVBoxLayout();
    viewportSplitter_->setLayout(viewportSplitLayout_);

    viewportSplitLayout_->addWidget(viewport);
    viewportSplitLayout_->addWidget(networkView);

    mainLayout_->addWidget(viewportSplitter_);
}
