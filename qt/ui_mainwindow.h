/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QOpenGLWidget *openGLWidget;
    QPushButton *pushButton;
    QSlider *horizontalSlider;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QSlider *horizontalSlider_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *Move_label;
    QSlider *horizontalSlider_5;
    QSlider *horizontalSlider_6;
    QSlider *horizontalSlider_7;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QLabel *label_6;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(875, 586);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 619, 499));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(630, 10, 83, 29));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(660, 210, 160, 16));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(360);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(660, 230, 160, 16));
        horizontalSlider_2->setMinimum(0);
        horizontalSlider_2->setMaximum(360);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(660, 250, 160, 16));
        horizontalSlider_3->setMinimum(0);
        horizontalSlider_3->setMaximum(360);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName(QString::fromUtf8("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(660, 170, 160, 16));
        horizontalSlider_4->setMinimum(-99);
        horizontalSlider_4->setMaximum(299);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(720, 150, 41, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(640, 210, 21, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(640, 230, 16, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(640, 250, 16, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(710, 190, 62, 16));
        Move_label = new QLabel(centralwidget);
        Move_label->setObjectName(QString::fromUtf8("Move_label"));
        Move_label->setGeometry(QRect(720, 270, 41, 16));
        horizontalSlider_5 = new QSlider(centralwidget);
        horizontalSlider_5->setObjectName(QString::fromUtf8("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(660, 290, 160, 16));
        horizontalSlider_5->setMinimum(-100);
        horizontalSlider_5->setMaximum(100);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        horizontalSlider_6 = new QSlider(centralwidget);
        horizontalSlider_6->setObjectName(QString::fromUtf8("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(660, 310, 160, 16));
        horizontalSlider_6->setMinimum(-100);
        horizontalSlider_6->setMaximum(100);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        horizontalSlider_7 = new QSlider(centralwidget);
        horizontalSlider_7->setObjectName(QString::fromUtf8("horizontalSlider_7"));
        horizontalSlider_7->setGeometry(QRect(660, 330, 160, 16));
        horizontalSlider_7->setMinimum(-100);
        horizontalSlider_7->setMaximum(100);
        horizontalSlider_7->setOrientation(Qt::Horizontal);
        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(630, 120, 121, 22));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(630, 100, 121, 22));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(710, 80, 81, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 875, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Rotation", nullptr));
        Move_label->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Central", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Parallel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Projection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
