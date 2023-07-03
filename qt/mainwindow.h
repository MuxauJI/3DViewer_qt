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
  void change_slider_position(int val, char dir);

 private slots:
  void on_open_button_clicked();
  void on_rotation_x_slider_valueChanged(int value);
  void on_rotation_y_slider_valueChanged(int value);
  void on_rotation_z_slider_valueChanged(int value);
  void on_scale_slider_valueChanged(int value);
  void on_move_x_slider_valueChanged(int value);
  void on_move_y_slider_valueChanged(int value);
  void on_move_z_slider_valueChanged(int value);
  void on_parallel_rbutton_toggled();
  void on_central_rbutton_toggled();
  void on_line_w_slider_valueChanged(int value);

 private:
  Ui::MainWindow *ui;
  void resizeEvent(QResizeEvent *);
  QGridLayout *layout;
  QWidget *view;
  Object_viewer *viewer;
};

#endif  // QT_MAINWINDOW_H_
