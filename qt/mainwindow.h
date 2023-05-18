#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGridLayout>
#include <QDebug>

#include "object_viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
 void on_pushButton_clicked();
 void on_horizontalSlider_valueChanged(int value);
 void on_horizontalSlider_2_valueChanged(int value);
 void on_horizontalSlider_3_valueChanged(int value);
 void on_horizontalSlider_4_valueChanged(int value);

 void on_horizontalSlider_5_valueChanged(int value);

 void on_horizontalSlider_6_valueChanged(int value);

 void on_horizontalSlider_7_valueChanged(int value);

 private:
    Ui::MainWindow *ui;
    QGridLayout *layout;
    QWidget *view;
    Object_viewer *viewer;
};

#endif // MAINWINDOW_H
