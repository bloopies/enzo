#include <QApplication>
#include <QPushButton>

int main()
{
    QApplication app (argc, argv);

    QPushButton button ("Hello world!");
    button.show();

    return app.exec();
}
