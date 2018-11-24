#include <QApplication>
#include <clocale>
#include "MainWindow.h"
#include "reg.h"

#include "ode_num_int/OptionalParameters.h"

int main(int argc, char *argv[])
{
    registerTypes();
    QApplication app(argc, argv);

    // Set "C" numeric locale because of decimal point
    setlocale( LC_NUMERIC, "C" );

    ctm::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
