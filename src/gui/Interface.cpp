#include "gui/Interface.h"
#include "gui/viewport/Viewport.h"
#include "gui/network/Network.h"
#include <qpushbutton.h>
#include <qsplitter.h>
#include <QTimer>

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


    viewportSplitter_ = new QSplitter(this);



    viewportSplitter_->addWidget(viewport);
    viewportSplitter_->addWidget(network);
    // viewportSplitter_->addWidget(new QPushButton("hello world"));

    viewportSplitter_->setStretchFactor(0, 10);
    viewportSplitter_->setStretchFactor(1, 1);

    mainLayout_->addWidget(viewportSplitter_);

    QTimer::singleShot(100, this, [=] {
    std::cout << "Viewport size: " << viewport->width() << " x " << viewport->height() << std::endl;
    std::cout << "Network size: " << network->width() << " x " << network->height() << std::endl;
});

}
