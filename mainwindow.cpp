#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <bits/stdc++.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <ctime>

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

struct ProcessInfo {
    int pid;
    QString name;
    QString resUsage; // For CPU/Memory usage (placeholder)
    QString virUsage;
};


long getProcessMemoryUsage(int pid) {
    QFile statmFile("/proc/" + QString::number(pid) + "/statm");
    if (!statmFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;  // Return -1 on failure

    QTextStream in(&statmFile);
    QString line = in.readLine();
    statmFile.close();

    if (!line.isEmpty()) {
        QStringList parts = line.split(" ");
        if (!parts.isEmpty()) {
            long pages = parts[0].toLong();
            long pageSize = sysconf(_SC_PAGESIZE); // Get page size in bytes
            return pages * pageSize / 1024;       // Convert to KB
        }
    }
    return -1;
}

long getProcessMemoryUsageFromStatus(int pid) {
    QFile statusFile("/proc/" + QString::number(pid) + "/status");
    if (!statusFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;  // Return -1 on failure

    QTextStream in(&statusFile);
    QString line;

    while (in.readLineInto(&line)) {
        if (line.startsWith("VmRSS:")) {
            QStringList parts = line.split(QRegExp("\\s+"));
            if (parts.size() > 1) {
                return parts[1].toLong(); // Memory usage in KB
            }
        }
    }

    return -1;  // Return -1 if VmRSS is not found
}


QVector<ProcessInfo> getActiveProcesses() {
    QVector<ProcessInfo> processes;
    QDir procDir("/proc");
    QStringList procEntries = procDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &entry : procEntries) {
        bool isPid = false;
        int pid = entry.toInt(&isPid);

        if (isPid) {
            QFile statusFile("/proc/" + entry + "/status");
            if (statusFile.open(QIODevice::ReadOnly)) {
                QTextStream in(&statusFile);
                QString line;
                QString name;

                while (in.readLineInto(&line)) {
                    if (line.startsWith("Name:")) {
                        name = line.split(QRegExp("\\s+"))[1];
                        break;
                    }
                }

                double resUsage = getProcessMemoryUsage(pid);
                double virUsage = getProcessMemoryUsageFromStatus(pid);

                processes.append({
                    pid,
                    name,
                    resUsage > 0 ? QString::number(resUsage / 1024.0, 'f', 2) + " MB" : "N/A",
                    virUsage > 0 ? QString::number(virUsage / 1024.0, 'f', 2) + " MB" : "N/A"
                });
            }
        }
    }
    return processes;
}

// struct ProcessDetails {
//     QString processId;
//     QString processName;
//     QString user;
//     QString status;
//     QString startTime;
//     QString priority;
//     QString controlGroup;
//     QString cpu;
//     QString cpuTime;
// };

ProcessDetails MainWindow::getProcessDetails(const QString &pid) {
    ProcessDetails details;
    details.processId = pid;

    // Get process name
    QFile commFile("/proc/" + pid + "/comm");
    if (commFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        details.processName = commFile.readLine().trimmed();
        commFile.close();
    } else {
        details.processName = "Unknown";
    }

    // Get user and status
    QFile statusFile("/proc/" + pid + "/status");
    if (statusFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&statusFile);
        QString line;
        while (in.readLineInto(&line)) {
            if (line.startsWith("Uid:")) {
                QStringList tokens = line.split(QRegExp("\\s+"));
                if (tokens.size() > 1) {
                    QString uid = tokens[1];
                    struct passwd *pwd = getpwuid(uid.toInt());
                    details.user = pwd ? QString(pwd->pw_name) : "Unknown";
                }
            } else if (line.startsWith("State:")) {
                details.status = line.split(QRegExp("\\s+"))[1];
            } else if (line.startsWith("Priority:")) {
                details.priority = line.split(QRegExp("\\s+"))[1];
            }
        }
        statusFile.close();
    } else {
        details.user = "Unknown";
        details.status = "Unknown";
        details.priority = "Unknown";
    }

    // Get CPU time and start time
    QFile statFile("/proc/" + pid + "/stat");
    if (statFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString line = statFile.readLine();
        QStringList tokens = line.split(QRegExp("\\s+"));
        if (tokens.size() > 16) {
            long utime = tokens[13].toLong();
            long stime = tokens[14].toLong();
            long startTimeTicks = tokens[21].toLong();
            long hertz = sysconf(_SC_CLK_TCK);

            details.cpuTime = QString::number((utime + stime) / static_cast<double>(hertz), 'f', 2) + " seconds";

            // Convert start time to a readable format
            time_t startTime = startTimeTicks / hertz;
            details.startTime = QString::fromStdString(std::asctime(std::localtime(&startTime))).trimmed();
        }
        statFile.close();
    } else {
        details.cpuTime = "Unknown";
        details.startTime = "Unknown";
    }

    // Get control group
    QFile cgroupFile("/proc/" + pid + "/cgroup");
    if (cgroupFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        details.controlGroup = cgroupFile.readAll().trimmed();
        cgroupFile.close();
    } else {
        details.controlGroup = "Unknown";
    }

    // Get CPU (dummy value as an example, this can be extended to fetch actual CPU info)
    details.cpu = "CPU0"; // Placeholder, extend if needed

    return details;
}

void MainWindow::on_processDetailButton_clicked() {
    int selectedRow = ui->processTable->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Process Selected", "Please select a process first.");
        return;
    }

    QString processId = ui->processTable->item(selectedRow, 1)->text(); // Assuming PID is in column 0
    ProcessDetails details = getProcessDetails(processId);

    QString processDetails = QString(
                                 "Process ID: %1\n"
                                 "Process Name: %2\n"
                                 "User: %3\n"
                                 "Status: %4\n"
                                 "Start Time: %5\n"
                                 "Priority: %6\n"
                                 "Control Group: %7\n"

                                 "CPU Time: %9"
                                 ).arg(details.processId)
                                 .arg(details.processName)
                                 .arg(details.user)
                                 .arg(details.status)
                                 .arg(details.startTime)
                                 .arg(details.priority)
                                 .arg(details.controlGroup)

                                 .arg(details.cpuTime);

    QMessageBox::information(this, "Process Details", processDetails);
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

QVector<double> readSpeedHistory; // Historical read speeds
QVector<double> writeSpeedHistory; // Historical write speeds
long long previousReadSectors = 0; // Previous total read sectors
long long previousWriteSectors = 0; // Previous total write sectors
double sectorSizeKB = 0.5; // Sector size in KB
int ioHistoryLength = 60; // Number of points on the I/O plot



void MainWindow::updateIOInfo() {
    IOInfo ioInfo = getIOInfo();

    // Calculate read/write speeds in MB
    long long deltaReadSectors = ioInfo.readSectors - previousReadSectors;
    long long deltaWriteSectors = ioInfo.writeSectors - previousWriteSectors;

    double readSpeedMB = (deltaReadSectors * sectorSizeKB) / 1024; // Convert to MB
    double writeSpeedMB = (deltaWriteSectors * sectorSizeKB) / 1024; // Convert to MB

    // Update previous values for the next calculation
    previousReadSectors = ioInfo.readSectors;
    previousWriteSectors = ioInfo.writeSectors;

    // Update labels to display MB
    ui->ioReadLabel->setText(QString("Total: %1 MB, Current: %2 MB/s")
                                 .arg((ioInfo.readSectors * sectorSizeKB) / 1024)
                                 .arg(readSpeedMB, 0, 'f', 2));
    ui->ioWriteLabel->setText(QString("Total: %1 MB, Current: %2 MB/s")
                                  .arg((ioInfo.writeSectors * sectorSizeKB) / 1024)
                                  .arg(writeSpeedMB, 0, 'f', 2));

    // Update plot data with read and write speeds in MB
    readSpeedHistory.pop_back();
    readSpeedHistory.push_front(readSpeedMB);

    writeSpeedHistory.pop_back();
    writeSpeedHistory.push_front(writeSpeedMB);

    QVector<double> xPoints(ioHistoryLength);
    for (int i = 0; i < ioHistoryLength; ++i) {
        xPoints[i] = i;
    }

    ui->ioPlot->graph(0)->setData(xPoints, readSpeedHistory); // Read speeds in MB
    ui->ioPlot->graph(1)->setData(xPoints, writeSpeedHistory); // Write speeds in MB

    // Adjust y-axis dynamically
    double maxSpeed = std::max(*std::max_element(readSpeedHistory.begin(), readSpeedHistory.end()),
                               *std::max_element(writeSpeedHistory.begin(), writeSpeedHistory.end()));
    ui->ioPlot->yAxis->setRange(0, std::max(maxSpeed * 1.1, 10.0)); // Add some headroom

    ui->ioPlot->replot();
}

void sortProcessesByName(QVector<ProcessInfo> &processes) {
    std::sort(processes.begin(), processes.end(), [](const ProcessInfo &a, const ProcessInfo &b) {
        return a.name < b.name; // Sort alphabetically
    });
}

void MainWindow::updateProcessList() {
    QVector<ProcessInfo> processes = getActiveProcesses();
    sortProcessesByName(processes);
    ui->processTable->setRowCount(processes.size());
    for (int i = 0; i < processes.size(); ++i) {

        ui->processTable->setItem(i, 0, new QTableWidgetItem(processes[i].name));
        ui->processTable->setItem(i, 1, new QTableWidgetItem(QString::number(processes[i].pid)));
        ui->processTable->setItem(i, 2, new QTableWidgetItem(processes[i].resUsage));
        ui->processTable->setItem(i, 3, new QTableWidgetItem(processes[i].virUsage));
    }
}


void MainWindow::terminateSelectedProcess() {
    QList<QTableWidgetItem*> selectedItems = ui->processTable->selectedItems();

    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "No Process Selected", "Please select a process to terminate.");
        return;
    }

    int selectedRow = selectedItems[0]->row();
    int pid = ui->processTable->item(selectedRow, 1)->text().toInt();

    // Terminate the process using system command
    QString command = "kill -9 " + QString::number(pid);
    int result = system(command.toStdString().c_str());

    if (result == 0) {
        QMessageBox::information(this, "Process Terminated", "Process " + QString::number(pid) + " terminated successfully.");
        updateProcessList();
    } else {
        QMessageBox::critical(this, "Error", "Failed to terminate process " + QString::number(pid) + ".");
    }
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

    // Initialize I/O history buffers
    readSpeedHistory.fill(0, ioHistoryLength);
    writeSpeedHistory.fill(0, ioHistoryLength);

    // Configure the I/O plot
    ui->ioPlot->addGraph(); // Graph 0 for read speeds
    ui->ioPlot->graph(0)->setPen(QPen(Qt::blue)); // Blue for read speeds

    ui->ioPlot->addGraph(); // Graph 1 for write speeds
    ui->ioPlot->graph(1)->setPen(QPen(Qt::red)); // Red for write speeds

    ui->ioPlot->xAxis->setRange(0, ioHistoryLength);
    ui->ioPlot->yAxis->setRange(0, 1024); // Adjust as needed for KB/s
    ui->ioPlot->xAxis->setLabel("Time (s)");
    ui->ioPlot->yAxis->setLabel("Speed (KB/s)");






    timer->start(1000);

    connect(ui->endProcessButton, &QPushButton::clicked, this, &MainWindow::terminateSelectedProcess);
    QTimer *processUpdateTimer = new QTimer(this);
    connect(processUpdateTimer, &QTimer::timeout, this, &MainWindow::updateProcessList);
    processUpdateTimer->start(3000);

}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


