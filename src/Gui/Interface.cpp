#include "Gui/Interface.h"
#include "Engine/Network/NetworkManager.h"
#include "Gui/ParametersPanel/ParametersPanel.h"
#include "Gui/Viewport/Viewport.h"
#include "Gui/Network/Network.h"
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <QTimer>
#include <Gui/UtilWidgets/Splitter.h>

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
    Network* network = new Network();
    ParametersPanel* parametersPanel = new ParametersPanel();

    constexpr int margin = 2;
    viewport->layout()->setContentsMargins(margin, margin, margin, margin);
    network->layout()->setContentsMargins(margin, margin, margin, margin);
    parametersPanel->layout()->setContentsMargins(margin, margin, margin, margin);
    mainLayout_->setContentsMargins(margin, margin, margin, margin);



    viewportSplitter_ = new Splitter(this);
    networkSplitter_ = new Splitter(this);
    networkSplitter_->setOrientation(Qt::Vertical);



    viewportSplitter_->addWidget(viewport);
    viewportSplitter_->addWidget(networkSplitter_);
    viewportSplitter_->setStretchFactor(0, 4);
    viewportSplitter_->setStretchFactor(1, 1);

    networkSplitter_->addWidget(parametersPanel);
    networkSplitter_->addWidget(network);
    networkSplitter_->setStretchFactor(0, 10);
    networkSplitter_->setStretchFactor(1, 1);

    mainLayout_->addWidget(viewportSplitter_);

    // connect signals
    connect(&enzo::nt::nm(), &enzo::nt::NetworkManager::updateDisplay, viewport, &Viewport::geometryChanged);
    enzo::nt::nm().displayNodeChanged.connect([parametersPanel](){parametersPanel->selectionChanged();});
    // connect(&enzo::nt::nm(), &enzo::nt::NetworkManager::updateDisplay, parametersPanel, &ParametersPanel::selectionChanged);

//  ─── end of EnzoUI ctor ───
QTimer::singleShot(0, this, [=] {
auto dump = [](const char* name, QWidget* w) {
    qInfo().nospace()
        << name
        << "  sizeHint="    << w->sizeHint()
        << "  minHint="     << w->minimumSizeHint()
        << "  min="         << w->minimumSize()
        << "  policy="      << w->sizePolicy();
};

    dump("Viewport        ", viewport);
    dump("ParametersPanel ", parametersPanel);
    dump("Network         ", network);
    dump("NetworkSplitter ", networkSplitter_);   // will show max(child‑mins)
});

}
