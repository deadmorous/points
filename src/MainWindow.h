// MainWindow.h

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>

namespace ctm {

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
};

} // namespace ctm

#endif // _MAINWINDOW_H_
