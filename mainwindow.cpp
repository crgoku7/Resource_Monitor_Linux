#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>

// Implement CPU, Memory, Network, and IO info retrieval functions here
double getCpuUsage() {
    static long long lastTotalUser = 0, lastTotalUserLow = 0, lastTotalSys = 0, lastTotalIdle = 0;

    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1.0;  // Return -1 on failure to read

    QTextStream in(&file);
    QString line = in.readLine();  // First line contains CPU data
    file.close();  // Always close the file after reading

    if (line.isEmpty()) {
        return -1.0;  // Handle empty lines
    }

    QStringList cpuData = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    if (cpuData.size() < 5) {
        return -1.0;  // Ensure we have enough fields
    }

    long long user = cpuData[1].toLongLong();
    long long nice = cpuData[2].toLongLong();
    long long system = cpuData[3].toLongLong();
    long long idle = cpuData[4].toLongLong();

    long long totalUser = user;
    long long totalUserLow = nice;
    long long totalSys = system;
    long long totalIdle = idle;

    long long total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
                      (totalSys - lastTotalSys) + (totalIdle - lastTotalIdle);

    long long totalIdleDelta = totalIdle - lastTotalIdle;

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    if (total == 0) return -1.0;  // Prevent division by zero

    double cpuUsage = 100.0 * (1.0 - (totalIdleDelta / static_cast<double>(total)));

    return cpuUsage;
}

double getMemoryUsage() {
    QFile file("/proc/meminfo");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1.0;

    QTextStream in(&file);
    long totalMemory = 0;
    long freeMemory = 0;
    QString line;

    while (in.readLineInto(&line)) {
        if (line.startsWith("MemTotal:")) {
            totalMemory = line.split(QRegExp("\\s+"))[1].toLong();
        }
        if (line.startsWith("MemFree:")) {
            freeMemory = line.split(QRegExp("\\s+"))[1].toLong();
        }
        if (totalMemory > 0 && freeMemory > 0) {
            break;
        }
    }

    file.close();  // Always close the file after reading

    if (totalMemory == 0) return -1.0;  // Avoid division by zero

    double usedMemory = totalMemory - freeMemory;
    double memoryUsage = (usedMemory / static_cast<double>(totalMemory)) * 100;
    return memoryUsage;
}

struct NetworkInfo {
    long long rxBytes;
    long long txBytes;
};

NetworkInfo getNetworkInfo() {
    QFile file("/proc/net/dev");
    NetworkInfo info = {0, 0};

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return info;  // Return default on failure

    QTextStream in(&file);
    QString line;

    // Skipping the first two header lines
    in.readLine();
    in.readLine();

    // Read data for each interface
    while (in.readLineInto(&line)) {
        QStringList netData = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (netData.size() > 9) {
            info.rxBytes += netData[1].toLongLong();  // Received bytes
            info.txBytes += netData[9].toLongLong();  // Transmitted bytes
        }
    }

    file.close();  // Always close the file after reading
    return info;
}

struct IOInfo {
    long long readSectors;
    long long writeSectors;
};

IOInfo getIOInfo() {
    QFile file("/proc/diskstats");
    IOInfo io = {0, 0};

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return io;  // Return default on failure

    QTextStream in(&file);
    QString line;

    while (in.readLineInto(&line)) {
        QStringList ioData = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (ioData.size() > 14) {
            io.readSectors += ioData[5].toLongLong();  // Sectors read
            io.writeSectors += ioData[9].toLongLong();  // Sectors written
        }
    }

    file.close();  // Always close the file after reading
    return io;
}

// Functions to update the UI with the latest data
void MainWindow::updateCpuUsage() {
    double cpuUsage = getCpuUsage();
    if (cpuUsage >= 0) {  // Check if data is valid
        ui->cpuProgressBar->setValue(static_cast<int>(cpuUsage));
    }
}

void MainWindow::updateMemoryUsage() {
    double memoryUsage = getMemoryUsage();
    if (memoryUsage >= 0) {  // Check if data is valid
        ui->memoryProgressBar->setValue(static_cast<int>(memoryUsage));
    }
}

void MainWindow::updateNetworkInfo() {
    NetworkInfo netInfo = getNetworkInfo();
    ui->networkRxLabel->setText(QString::number(netInfo.rxBytes / 1024) + " KB received");
    ui->networkTxLabel->setText(QString::number(netInfo.txBytes / 1024) + " KB transmitted");
}

void MainWindow::updateIOInfo() {
    IOInfo ioInfo = getIOInfo();
    ui->ioReadLabel->setText(QString::number(ioInfo.readSectors) + " sectors read");
    ui->ioWriteLabel->setText(QString::number(ioInfo.writeSectors) + " sectors written");
}

// Constructor to set up the UI and the update timer
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up a timer to update the stats periodically
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCpuUsage);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateMemoryUsage);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateNetworkInfo);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateIOInfo);
    timer->start(1000);  // Update every second
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
