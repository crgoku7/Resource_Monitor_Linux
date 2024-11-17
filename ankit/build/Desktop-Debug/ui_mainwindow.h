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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTabWidget>
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
    QLabel *ioReadLabel;
    QLabel *ioWriteLabel;
    QWidget *tab_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(802, 847);
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
        ioReadLabel = new QLabel(DiskBox);
        ioReadLabel->setObjectName(QString::fromUtf8("ioReadLabel"));
        ioReadLabel->setGeometry(QRect(40, 50, 671, 18));
        ioWriteLabel = new QLabel(DiskBox);
        ioWriteLabel->setObjectName(QString::fromUtf8("ioWriteLabel"));
        ioWriteLabel->setGeometry(QRect(40, 90, 681, 18));

        verticalLayout_2->addWidget(DiskBox);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

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
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
