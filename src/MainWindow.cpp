// MainWindow.cpp

#include "MainWindow.h"
#include "ParamView.h"
#include "ParamModel.h"
#include "TaskConfig.h"
#include "PointsView.h"

#include <QDockWidget>
#include <QLabel>
#include <QToolBar>
#include <QStatusBar>

namespace ctm {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create parameters view in a dock
    auto dock = new QDockWidget(tr("Parameters"), this);
    dock->setMinimumWidth(300);
    auto paramView = new ParamView;
    auto paramProvider = points::TaskConfig::cfg().parameterProvider();
    const OptionalParameters* paramProviderAsOptionalParameters = paramProvider;
    paramView->setSource(const_cast<OptionalParameters*>(paramProviderAsOptionalParameters));
    dock->setWidget(paramView);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    // Create points view
    auto pointsView = new points::PointsView;
    setCentralWidget(pointsView);

    // Create toolbar
    auto toolbar = addToolBar(tr("General"));
    toolbar->addAction(QIcon(":/points/play.svg"), tr("Start simulation"));
    toolbar->addAction(QIcon(":/points/stop.svg"), tr("Stop simulation"));

    // Create status bar
    auto statusBar = new QStatusBar;
    setStatusBar(statusBar);

    // Show editing failure messages in the status bar
    connect(paramView->model(), &ParamModel::editingFailed, [statusBar](const QString msg) {
        statusBar->showMessage(msg, 3000);
    });

    // Update points view when the initial state changes
    connect(paramView->model(), &ParamModel::dataChanged, [paramProvider, pointsView](const QModelIndex &index) {
        for (auto i=index.siblingAtColumn(0); i.isValid(); i=i.parent())
            if (i.data().toString() == "init_state") {
                auto initState = paramProvider->initState();
                pointsView->setData(initState? initState->initialState(): points::V());
                return;
            }
    });
}

} // namespace ctm
