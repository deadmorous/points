// MainWindow.cpp

#include "MainWindow.h"
#include "ParamView.h"
#include "ParamModel.h"
#include "TaskConfig.h"

#include <QDockWidget>
#include <QLabel>
#include <QStatusBar>

namespace ctm {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    auto dock = new QDockWidget(tr("Parameters"), this);
    dock->setMinimumWidth(300);
    auto paramView = new ParamView;

    const OptionalParameters* paramProvider = points::TaskConfig::cfg().parameterProvider();
    paramView->setSource(const_cast<OptionalParameters*>(paramProvider));
    dock->setWidget(paramView);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    setCentralWidget(new QLabel("hello"));

    auto statusBar = new QStatusBar;
    setStatusBar(statusBar);
    connect(paramView->model(), &ParamModel::editingFailed, [statusBar](const QString msg) {
        statusBar->showMessage(msg, 3000);
    });
}

} // namespace ctm
