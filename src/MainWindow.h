// MainWindow.h

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "SimulationRunner.h"

namespace ctm {

class ParamView;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ParamView *paramView();

private:
    ParamView *m_paramView;
    SimulationRunner m_runner;
};

} // namespace ctm

#endif // _MAINWINDOW_H_
