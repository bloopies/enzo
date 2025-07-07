#include "gui/Interface.h"
#include "Engine/Network/NetworkManager.h"
#include "gui/viewport/Viewport.h"
#include "gui/network/Network.h"
#include <qpushbutton.h>
#include <qsplitter.h>
#include <QTimer>
#include <gui/UtilWidgets/Splitter.h>

EnzoUI::EnzoUI()
{
    // layout
    mainLayout_ = new QVBoxLayout(this);
    setLayout(mainLayout_);

    // title and size
    setWindowTitle("Enzo");
    constexpr float scale = 0.8;
    resize(1920*scale, 1080*scale);

    // TODO: unify stylsheet
    setStyleSheet("background-color:#1d2021;");

    Viewport* viewport = new Viewport();
    Network* network = new Network(this);

    constexpr int margin = 2;
    viewport->layout()->setContentsMargins(margin, margin, margin, margin);
    network->layout()->setContentsMargins(margin, margin, margin, margin);
    mainLayout_->setContentsMargins(margin, margin, margin, margin);


    viewportSplitter_ = new Splitter(this);



    viewportSplitter_->addWidget(viewport);
    viewportSplitter_->addWidget(network);
    // viewportSplitter_->addWidget(new QPushButton("hello world"));

    viewportSplitter_->setStretchFactor(0, 20);
    viewportSplitter_->setStretchFactor(1, 1);

    mainLayout_->addWidget(viewportSplitter_);

    // connect signals
    connect(enzo::nt::NetworkManager::getInstance(), &enzo::nt::NetworkManager::updateDisplay, viewport, &Viewport::geometryChanged);

}
