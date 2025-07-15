#include <QApplication>
#include <QPushButton>
#include <QSurfaceFormat>
#include "Engine/Operator/OperatorTable.h"
#include <boost/dll/import.hpp>

#include "Interface.h"

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

    EnzoUI interface;
    interface.show();

    return app.exec();
}
