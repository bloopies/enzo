#include "gui/Interface.h"
#include "gui/viewport/Viewport.h"
#include "gui/network/NetworkView.h"
#include <qpushbutton.h>
#include <qsplitter.h>

EnzoUI::EnzoUI()
{
    // layout
    mainLayout_ = new QVBoxLayout(this);
    setLayout(mainLayout_);

    // title and size
    setWindowTitle("Enzo");
    setMinimumSize(1920/2, 1080/2);

    Viewport* viewport = new Viewport();
    NetworkView* networkView = new NetworkView(this);
    networkView->setMinimumWidth(400);

    viewportSplitter_ = new QSplitter(this);

    viewportSplitter_->addWidget(viewport);
    viewportSplitter_->addWidget(networkView);

    mainLayout_->addWidget(viewportSplitter_);
}
