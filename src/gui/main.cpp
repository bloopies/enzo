#include <QApplication>
#include <QPushButton>
#include <QSurfaceFormat>

#include "Interface.h"

int main(int argc, char **argv)
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication app (argc, argv);

    EnzoUI interface;
    interface.show();

    return app.exec();
}
