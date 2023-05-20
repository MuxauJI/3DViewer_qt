#ifndef QT_MAINWINDOW_H_
#define QT_MAINWINDOW_H_

#include <QDebug>
#include <QFileDialog>
#include <QGridLayout>
#include <QMainWindow>
#include <QSettings>

#include "object_viewer.h"

#define ORGANIZATION_NAME "School21"
#define ORGANIZATION_DOMAIN "www.21-school.ru"
#define APPLICATION_NAME "3DViewer"
#define PROJECTION "PROJECTION"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void loadSettings();
  void saveSettings();
 public slots:
  void on_horizontalSlider_valueChanged(int value);

 private slots:
  void on_pushButton_clicked();

  void on_horizontalSlider_2_valueChanged(int value);
  void on_horizontalSlider_3_valueChanged(int value);
  void on_horizontalSlider_4_valueChanged(int value);

  void on_horizontalSlider_5_valueChanged(int value);

  void on_horizontalSlider_6_valueChanged(int value);

  void on_horizontalSlider_7_valueChanged(int value);

  void on_radioButton_toggled();

  void on_radioButton_2_toggled();

 private:
  Ui::MainWindow *ui;
  QGridLayout *layout;
  QWidget *view;
  Object_viewer *viewer;
};

#endif  // QT_MAINWINDOW_H_
