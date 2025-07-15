#include <QApplication>
#include <QPushButton>
#include <QSurfaceFormat>
#include "Engine/Operator/OperatorTable.h"
#include <boost/dll/import.hpp>

#include "Interface.h"
#include "Gui/Network/TabMenu.h"
#include <iostream>
#include <QTimer>

int main(int argc, char **argv)
{
    // set up rendering
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    // setup table
    auto initPlugin = boost::dll::import_symbol<void(void (*addOperator)(enzo::nt::opConstructor))>(
        "build/src/OpDefs/libenzoOps1.so", "newSopOperator"
    );

    initPlugin(enzo::op::OperatorTable::addOperator);


    QApplication app (argc, argv);

    QPoint cursorPos = QCursor::pos();

    EnzoUI interface;
    interface.show();

    enzo::ui::TabMenu tabMenu(&interface);
    QTimer::singleShot(1000, [&]{
        QPoint cursorPos = QCursor::pos();
        std::cout << cursorPos.x() << " " << cursorPos.y() << "\n";
        tabMenu.showOnMouse();
    });



    return app.exec();
}
