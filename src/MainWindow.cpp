// MainWindow.cpp

#include "MainWindow.h"
#include "ParamView.h"

#include <QDockWidget>
#include <QLabel>

namespace ctm {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto dock = new QDockWidget(tr("Parameters"), this);
    dock->setWidget(new ParamView);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    setCentralWidget(new QLabel("hello"));
}

} // namespace ctm
