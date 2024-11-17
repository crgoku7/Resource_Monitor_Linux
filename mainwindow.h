#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Declare your update functions here
    void updateCpuUsage();
    void updateMemoryUsage();
    void updateNetworkInfo();
    void updateIOInfo();
    qint64 previousRxBytes = 0;
    qint64 previousTxBytes = 0;
    QElapsedTimer networkTimer;
};
#endif // MAINWINDOW_H
