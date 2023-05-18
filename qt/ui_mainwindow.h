/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
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
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(875, 586);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName("openGLWidget");
        openGLWidget->setGeometry(QRect(0, 0, 619, 499));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(630, 10, 83, 29));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setGeometry(QRect(660, 110, 160, 16));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(360);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider_2 = new QSlider(centralwidget);
        horizontalSlider_2->setObjectName("horizontalSlider_2");
        horizontalSlider_2->setGeometry(QRect(660, 130, 160, 16));
        horizontalSlider_2->setMinimum(0);
        horizontalSlider_2->setMaximum(360);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(centralwidget);
        horizontalSlider_3->setObjectName("horizontalSlider_3");
        horizontalSlider_3->setGeometry(QRect(660, 150, 160, 16));
        horizontalSlider_3->setMinimum(0);
        horizontalSlider_3->setMaximum(360);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_4 = new QSlider(centralwidget);
        horizontalSlider_4->setObjectName("horizontalSlider_4");
        horizontalSlider_4->setGeometry(QRect(660, 70, 160, 16));
        horizontalSlider_4->setMinimum(-99);
        horizontalSlider_4->setMaximum(99);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(720, 50, 41, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(640, 110, 21, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(640, 130, 16, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(640, 150, 16, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(710, 90, 62, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
