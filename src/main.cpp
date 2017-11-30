#include <QApplication>
#include <QLabel>
#include "points_ode.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel label("hello");
    label.show();
    return app.exec();
}
