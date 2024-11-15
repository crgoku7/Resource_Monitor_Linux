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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *CPUBox;
    QProgressBar *cpuProgressBar;
    QGroupBox *NetworkBox;
    QLabel *networkRxLabel;
    QLabel *networkTxLabel;
    QGroupBox *MemoryBox;
    QProgressBar *memoryProgressBar;
    QGroupBox *DiskBox;
    QLabel *ioReadLabel;
    QLabel *ioWriteLabel;
    QWidget *tab_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(808, 741);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        CPUBox = new QGroupBox(tab);
        CPUBox->setObjectName(QString::fromUtf8("CPUBox"));
        CPUBox->setGeometry(QRect(20, 30, 741, 121));
        cpuProgressBar = new QProgressBar(CPUBox);
        cpuProgressBar->setObjectName(QString::fromUtf8("cpuProgressBar"));
        cpuProgressBar->setGeometry(QRect(40, 60, 118, 23));
        cpuProgressBar->setValue(24);
        NetworkBox = new QGroupBox(tab);
        NetworkBox->setObjectName(QString::fromUtf8("NetworkBox"));
        NetworkBox->setGeometry(QRect(20, 190, 741, 131));
        networkRxLabel = new QLabel(NetworkBox);
        networkRxLabel->setObjectName(QString::fromUtf8("networkRxLabel"));
        networkRxLabel->setGeometry(QRect(40, 40, 631, 18));
        networkTxLabel = new QLabel(NetworkBox);
        networkTxLabel->setObjectName(QString::fromUtf8("networkTxLabel"));
        networkTxLabel->setGeometry(QRect(40, 80, 681, 18));
        MemoryBox = new QGroupBox(tab);
        MemoryBox->setObjectName(QString::fromUtf8("MemoryBox"));
        MemoryBox->setGeometry(QRect(20, 360, 741, 131));
        memoryProgressBar = new QProgressBar(MemoryBox);
        memoryProgressBar->setObjectName(QString::fromUtf8("memoryProgressBar"));
        memoryProgressBar->setGeometry(QRect(40, 60, 118, 23));
        memoryProgressBar->setValue(24);
        DiskBox = new QGroupBox(tab);
        DiskBox->setObjectName(QString::fromUtf8("DiskBox"));
        DiskBox->setGeometry(QRect(20, 530, 741, 141));
        ioReadLabel = new QLabel(DiskBox);
        ioReadLabel->setObjectName(QString::fromUtf8("ioReadLabel"));
        ioReadLabel->setGeometry(QRect(40, 50, 671, 18));
        ioWriteLabel = new QLabel(DiskBox);
        ioWriteLabel->setObjectName(QString::fromUtf8("ioWriteLabel"));
        ioWriteLabel->setGeometry(QRect(40, 90, 681, 18));
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
        CPUBox->setTitle(QCoreApplication::translate("MainWindow", "CPU", nullptr));
        NetworkBox->setTitle(QCoreApplication::translate("MainWindow", "Network Usage", nullptr));
        networkRxLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        networkTxLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        MemoryBox->setTitle(QCoreApplication::translate("MainWindow", "Memory Usage", nullptr));
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
