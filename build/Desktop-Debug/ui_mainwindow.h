/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *cpuPlotLayout;
    QFrame *cpuLabelFrame;
    QGroupBox *NetworkBox;
    QVBoxLayout *verticalLayout_4;
    QCustomPlot *networkPlot;
    QLabel *networkRxLabel;
    QLabel *networkTxLabel;
    QGroupBox *MemoryBox;
    QVBoxLayout *verticalLayout_5;
    QCustomPlot *memoryPlot;
    QLabel *memoryUsageLabel;
    QGroupBox *DiskBox;
    QVBoxLayout *verticalLayout_6;
    QCustomPlot *ioPlot;
    QLabel *ioReadLabel;
    QLabel *ioWriteLabel;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_7;
    QTableWidget *processTable;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *endProcessButton;
    QPushButton *processDetailButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(756, 1175);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 280));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        cpuPlotLayout = new QCustomPlot(groupBox);
        cpuPlotLayout->setObjectName(QString::fromUtf8("cpuPlotLayout"));
        cpuPlotLayout->setMinimumSize(QSize(0, 150));

        verticalLayout_3->addWidget(cpuPlotLayout);

        cpuLabelFrame = new QFrame(groupBox);
        cpuLabelFrame->setObjectName(QString::fromUtf8("cpuLabelFrame"));
        cpuLabelFrame->setMinimumSize(QSize(0, 80));
        cpuLabelFrame->setFrameShape(QFrame::StyledPanel);
        cpuLabelFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(cpuLabelFrame);


        verticalLayout_2->addWidget(groupBox);

        NetworkBox = new QGroupBox(tab);
        NetworkBox->setObjectName(QString::fromUtf8("NetworkBox"));
        verticalLayout_4 = new QVBoxLayout(NetworkBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        networkPlot = new QCustomPlot(NetworkBox);
        networkPlot->setObjectName(QString::fromUtf8("networkPlot"));
        networkPlot->setMinimumSize(QSize(0, 130));

        verticalLayout_4->addWidget(networkPlot);

        networkRxLabel = new QLabel(NetworkBox);
        networkRxLabel->setObjectName(QString::fromUtf8("networkRxLabel"));

        verticalLayout_4->addWidget(networkRxLabel);

        networkTxLabel = new QLabel(NetworkBox);
        networkTxLabel->setObjectName(QString::fromUtf8("networkTxLabel"));

        verticalLayout_4->addWidget(networkTxLabel);


        verticalLayout_2->addWidget(NetworkBox);

        MemoryBox = new QGroupBox(tab);
        MemoryBox->setObjectName(QString::fromUtf8("MemoryBox"));
        verticalLayout_5 = new QVBoxLayout(MemoryBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        memoryPlot = new QCustomPlot(MemoryBox);
        memoryPlot->setObjectName(QString::fromUtf8("memoryPlot"));
        memoryPlot->setMinimumSize(QSize(0, 120));

        verticalLayout_5->addWidget(memoryPlot);

        memoryUsageLabel = new QLabel(MemoryBox);
        memoryUsageLabel->setObjectName(QString::fromUtf8("memoryUsageLabel"));

        verticalLayout_5->addWidget(memoryUsageLabel);


        verticalLayout_2->addWidget(MemoryBox);

        DiskBox = new QGroupBox(tab);
        DiskBox->setObjectName(QString::fromUtf8("DiskBox"));
        verticalLayout_6 = new QVBoxLayout(DiskBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        ioPlot = new QCustomPlot(DiskBox);
        ioPlot->setObjectName(QString::fromUtf8("ioPlot"));
        ioPlot->setMinimumSize(QSize(0, 120));

        verticalLayout_6->addWidget(ioPlot);

        ioReadLabel = new QLabel(DiskBox);
        ioReadLabel->setObjectName(QString::fromUtf8("ioReadLabel"));

        verticalLayout_6->addWidget(ioReadLabel);

        ioWriteLabel = new QLabel(DiskBox);
        ioWriteLabel->setObjectName(QString::fromUtf8("ioWriteLabel"));

        verticalLayout_6->addWidget(ioWriteLabel);


        verticalLayout_2->addWidget(DiskBox);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_7 = new QVBoxLayout(tab_2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        processTable = new QTableWidget(tab_2);
        if (processTable->columnCount() < 4)
            processTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        processTable->setObjectName(QString::fromUtf8("processTable"));
        processTable->setMinimumSize(QSize(0, 0));
        processTable->setMaximumSize(QSize(16777215, 16777215));
        processTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        processTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        processTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        processTable->setAlternatingRowColors(true);
        processTable->setSelectionMode(QAbstractItemView::SingleSelection);
        processTable->setSelectionBehavior(QAbstractItemView::SelectItems);
        processTable->setSortingEnabled(false);
        processTable->setColumnCount(4);
        processTable->horizontalHeader()->setCascadingSectionResizes(true);
        processTable->horizontalHeader()->setMinimumSectionSize(100);
        processTable->horizontalHeader()->setDefaultSectionSize(172);
        processTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        processTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_7->addWidget(processTable);

        frame = new QFrame(tab_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        endProcessButton = new QPushButton(frame);
        endProcessButton->setObjectName(QString::fromUtf8("endProcessButton"));

        horizontalLayout->addWidget(endProcessButton);

        processDetailButton = new QPushButton(frame);
        processDetailButton->setObjectName(QString::fromUtf8("processDetailButton"));

        horizontalLayout->addWidget(processDetailButton);


        verticalLayout_7->addWidget(frame);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "CPUBox", nullptr));
        NetworkBox->setTitle(QCoreApplication::translate("MainWindow", "Network Usage", nullptr));
        networkRxLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        networkTxLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        MemoryBox->setTitle(QCoreApplication::translate("MainWindow", "Memory Usage", nullptr));
        memoryUsageLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        DiskBox->setTitle(QCoreApplication::translate("MainWindow", "Disk Usage", nullptr));
        ioReadLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        ioWriteLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem = processTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = processTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = processTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Resident Memory", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = processTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Virtual Memory", nullptr));
        endProcessButton->setText(QCoreApplication::translate("MainWindow", "End Process", nullptr));
        processDetailButton->setText(QCoreApplication::translate("MainWindow", "Process Details", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
