#include <QApplication>
#include <QPushButton>

#include "Interface.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    EnzoUI interface;
    interface.show();

    return app.exec();
}
