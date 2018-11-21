// MainWindow.cpp

#include "MainWindow.h"
#include "ParamView.h"
#include "points_ode.h"

#include <QDockWidget>
#include <QLabel>

namespace ctm {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto dock = new QDockWidget(tr("Parameters"), this);
    auto paramView = new ParamView;
    paramView->setSource(std::make_shared<points::PointsOdeRhs>()); // TODO better
    dock->setWidget(paramView);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    setCentralWidget(new QLabel("hello"));
}

} // namespace ctm
