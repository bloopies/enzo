#include <QApplication>
#include <QPushButton>
#include <QSurfaceFormat>
#include "Engine/Operator/OperatorTable.h"

#include "Interface.h"

int main(int argc, char **argv)
{
    // set up rendering
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    enzo::op::OperatorTable::initPlugins();


    QApplication app (argc, argv);

    EnzoUI interface;
    interface.show();

    return app.exec();
}
