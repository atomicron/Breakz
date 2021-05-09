#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "breakz.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Breakz* breakz;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent*event);

private slots:
    void timeChangedWork(const QTime&);
    void timeChangedBreak(const QTime&);
    void startPressed();
    void startFromBreakPressed();
    void quitPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
