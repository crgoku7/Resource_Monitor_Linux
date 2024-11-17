#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <bits/stdc++.h>

QVector<QVector<double>> cpuUsageVector(13,QVector<double>(60,0));

// Implement CPU, Memory, Network, and IO info retrieval functions here
QVector<double> getCpuUsages() {
    static QVector<long long> lastUser, lastNice, lastSystem, lastIdle;
    QVector<double> cpuUsages;

    QFile file("/proc/stat");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return cpuUsages;

    QTextStream in(&file);
    QString line;
    QVector<long long> user, nice, system, idle;

    // Read CPU stats for each core
    while (in.readLineInto(&line)) {
        if (line.startsWith("cpu")) {
            QStringList cpuData = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            user.append(cpuData[1].toLongLong());
            nice.append(cpuData[2].toLongLong());
            system.append(cpuData[3].toLongLong());
            idle.append(cpuData[4].toLongLong());

            if (lastUser.size() < user.size()) {
                lastUser.resize(user.size());
                lastNice.resize(nice.size());
                lastSystem.resize(system.size());
                lastIdle.resize(idle.size());
            }
        }
    }

    for (int i = 0; i < user.size(); ++i) {
        long long totalUser = user[i];
        long long totalNice = nice[i];
        long long totalSystem = system[i];
        long long totalIdle = idle[i];

        long long total = (totalUser - lastUser[i]) + (totalNice - lastNice[i]) +
                          (totalSystem - lastSystem[i]) + (totalIdle - lastIdle[i]);

        long long totalIdleDelta = totalIdle - lastIdle[i];

        lastUser[i] = totalUser;
        lastNice[i] = totalNice;
        lastSystem[i] = totalSystem;
        lastIdle[i] = totalIdle;

        double cpuUsage = 100.0 * (1.0 - (totalIdleDelta / (double)total));
        cpuUsages.append(cpuUsage);
    }

    return cpuUsages;
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
    qint64 rxBytes; // Total received bytes
    qint64 txBytes; // Total transmitted bytes
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
bool legendCreated = false;
QVector<QLabel*> usageLabels;
void MainWindow::updateCpuUsage() {
    QVector<double> cpuUsage = getCpuUsages();
    int coreCount = cpuUsage.size();
    for (int i = 0; i<cpuUsage.size();i++){
        cpuUsageVector[i].push_front(cpuUsage[i]);
    }

    QVector<double> points(60,0);
    for(int i = 0;i<60;i++){
        points[i] = i;
    }



    auto cpuPlotLayout = ui->cpuPlotLayout;
    cpuPlotLayout->xAxis->setRange(0, 60);
    cpuPlotLayout->yAxis->setRange(0, 100);
    cpuPlotLayout->clearPlottables();


    for(int i = 0;i<cpuUsage.size();i++){
        QCPGraph *graph = cpuPlotLayout->addGraph();
        if(i == 0){
            graph->setName("CPU AVG");
        }
        else{
            graph->setName("CPU" + QString::number(i));
        }

        graph->setPen(QPen(QColor::fromHsv((i * 30) % 360, 255, 255)));

        QVector<double> usage(60,0);
        for(int j = 0; j<60;j++){
            usage[j] = cpuUsageVector[i][j];
        }
        graph->data()->clear();
        graph->setData(points,usage);

    }

    if (!legendCreated) {
        QGridLayout *gridLayout = new QGridLayout(ui->cpuLabelFrame);
        ui->cpuLabelFrame->setLayout(gridLayout);

        for (int i = 0; i < coreCount; i++) {
            QColor color = QColor::fromHsv((i * 30) % 360, 255, 255);

            QWidget *legendEntry = new QWidget(ui->cpuLabelFrame);
            QHBoxLayout *entryLayout = new QHBoxLayout(legendEntry);
            entryLayout->setContentsMargins(0, 0, 0, 0);

            QLabel *colorBox = new QLabel();
            colorBox->setFixedSize(15, 15);
            colorBox->setStyleSheet(QString("background-color: %1; border: 1px solid black;").arg(color.name()));

            QLabel *label;
            if(i == 0){
                label = new QLabel("CPU AVG");
            }
            else{
                label = new QLabel("CPU " + QString::number(i));
            }


            QLabel *usageLabel = new QLabel("0%"); // Initial usage set to 0%
            usageLabels.append(usageLabel); // Store reference for updating dynamically

            entryLayout->addWidget(colorBox);
            entryLayout->addWidget(label);
            entryLayout->addWidget(usageLabel);
            entryLayout->addStretch();

            legendEntry->setLayout(entryLayout);

            // Add legend entry to grid layout (4 per row)
            int row = i / 4;
            int col = i % 4;
            gridLayout->addWidget(legendEntry, row, col);
        }

        legendCreated = true;
    }

    // Update usage percentages in the legend
    for (int i = 0; i < coreCount; i++) {
        usageLabels[i]->setText(QString::number(cpuUsage[i], 'f', 1) + "%");
    }

    cpuPlotLayout->replot();
    cpuPlotLayout->update();


}

QVector<double> memoryUsageHistory; // Store memory usage values for the plot
int memoryHistoryLength = 60;       // Number of points on the memory usage plot


void MainWindow::updateMemoryUsage() {
    double memoryUsage = getMemoryUsage();
    if (memoryUsage < 0) return; // Invalid data, skip update

    // Update memory usage label
    ui->memoryUsageLabel->setText(QString("Current Memory Usage: %1%").arg(memoryUsage, 0, 'f', 2));

    // Update memory usage history
    memoryUsageHistory.pop_back();
    memoryUsageHistory.push_front(memoryUsage);

    // Generate X-axis points
    QVector<double> xPoints(memoryHistoryLength);
    for (int i = 0; i < memoryHistoryLength; ++i) {
        xPoints[i] = i;
    }

    // Update memory usage plot
    ui->memoryPlot->graph(0)->setData(xPoints, memoryUsageHistory);

    // Replot with updated data
    ui->memoryPlot->replot();
}

QVector<double> rxRateHistory;  // Store Rx rates for plotting
QVector<double> txRateHistory;  // Store Tx rates for plotting
int networkHistoryLength = 60;  // Number of points on the plot


void MainWindow::updateNetworkInfo() {
    NetworkInfo netInfo = getNetworkInfo();

    // Calculate elapsed time in seconds
    double elapsedTime = networkTimer.restart() / 1000.0; // Restart timer and get elapsed time in seconds

    // Calculate rates (in KB/s)
    double rxRate = (netInfo.rxBytes - previousRxBytes) / 1024.0 / elapsedTime;
    double txRate = (netInfo.txBytes - previousTxBytes) / 1024.0 / elapsedTime;

    // Update total and current rate labels
    ui->networkRxLabel->setText(
        QString("Sent Total: %1 KB, Current: %2 KB/s").arg(netInfo.rxBytes / 1024).arg(rxRate, 0, 'f', 2));
    ui->networkTxLabel->setText(
        QString("Received Total: %1 KB, Current: %2 KB/s").arg(netInfo.txBytes / 1024).arg(txRate, 0, 'f', 2));

    // Update plot data
    rxRateHistory.pop_back();
    rxRateHistory.push_front(rxRate);

    txRateHistory.pop_back();
    txRateHistory.push_front(txRate);

    QVector<double> xPoints(networkHistoryLength);
    for (int i = 0; i < networkHistoryLength; ++i) {
        xPoints[i] = i;
    }

    ui->networkPlot->graph(0)->setData(xPoints, rxRateHistory); // Rx graph
    ui->networkPlot->graph(1)->setData(xPoints, txRateHistory); // Tx graph

    // Adjust y-axis dynamically based on data
    double maxRate = std::max(*std::max_element(rxRateHistory.begin(), rxRateHistory.end()),
                              *std::max_element(txRateHistory.begin(), txRateHistory.end()));
    ui->networkPlot->yAxis->setRange(0, std::max(maxRate * 1.1, 10.0)); // Add some headroom

    ui->networkPlot->replot();

    // Store current values for the next update
    previousRxBytes = netInfo.rxBytes;
    previousTxBytes = netInfo.txBytes;
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
    rxRateHistory.fill(0, networkHistoryLength);
    txRateHistory.fill(0, networkHistoryLength);

    // Configure the network plot
    ui->networkPlot->addGraph(); // Graph 0 for Rx
    ui->networkPlot->graph(0)->setPen(QPen(Qt::blue)); // Blue for Rx

    ui->networkPlot->addGraph(); // Graph 1 for Tx
    ui->networkPlot->graph(1)->setPen(QPen(Qt::red)); // Red for Tx

    ui->networkPlot->xAxis->setRange(0, networkHistoryLength);
    ui->networkPlot->yAxis->setRange(0, 1024); // Adjust as needed (e.g., 1024 KB/s)
    ui->networkPlot->xAxis->setLabel("Time (s)");
    ui->networkPlot->yAxis->setLabel("Rate (KB/s)");

    memoryUsageHistory.fill(0, memoryHistoryLength); // Initialize memory usage history

    // Configure the memory plot
    ui->memoryPlot->addGraph();
    ui->memoryPlot->graph(0)->setPen(QPen(Qt::green)); // Green for memory usage
    ui->memoryPlot->xAxis->setRange(0, memoryHistoryLength);
    ui->memoryPlot->yAxis->setRange(0, 100); // Memory usage as a percentage
    ui->memoryPlot->xAxis->setLabel("Time (s)");
    ui->memoryPlot->yAxis->setLabel("Usage (%)");


    timer->start(1000);  // Update every 1/10 second

}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
