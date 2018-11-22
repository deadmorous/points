#include <QApplication>
#include "MainWindow.h"
#include "reg.h"

#include "ode_num_int/OptionalParameters.h"

int main(int argc, char *argv[])
{
    registerTypes();
    QApplication app(argc, argv);
    ctm::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
