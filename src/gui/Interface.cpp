#include "gui/Interface.h"
#include "gui/Viewport.h"
#include "gui/NetworkView.h"
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

    viewportSplitter_ = new QSplitter(this);

    viewportSplitter_->addWidget(viewport);
    viewportSplitter_->addWidget(networkView);

    mainLayout_->addWidget(viewportSplitter_);
}
