#include <QApplication>
#include "points_ode.h"
#include "MainWindow.h"

#include "ode_num_int/OptionalParameters.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ctm::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
