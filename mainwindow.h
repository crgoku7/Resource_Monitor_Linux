#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include "qcustomplot.h"
#include <QProcess>

struct ProcessDetails {
    QString processId;
    QString processName;
    QString user;
    QString status;
    QString startTime;
    QString priority;
    QString controlGroup;
    QString cpu;
    QString cpuTime;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ProcessDetails getProcessDetails(const QString &pid);
    ~MainWindow();

private slots:
    void updateProcessList();
    void terminateSelectedProcess();
    void on_processDetailButton_clicked();

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
    QVector<QProcess*> processList;
};
#endif // MAINWINDOW_H
