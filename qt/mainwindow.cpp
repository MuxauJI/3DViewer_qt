
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  layout = new QGridLayout();
  viewer = new Object_viewer();
  view = (QWidget *)(viewer);
  layout->addWidget(view);
  ui->radioButton->setChecked(true);
  ui->openGLWidget->setLayout(layout);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QString fileName_open;
  fileName_open =
      QFileDialog::getOpenFileName(this, "Open file ...", "~/", "*.obj",
                                   nullptr, QFileDialog::DontUseNativeDialog);
  if (fileName_open.isNull()) {
    return;
  } else {
    QByteArray tmp = fileName_open.toLocal8Bit();
    viewer->filename_open = tmp.data();
    viewer->init_facets();
  }
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  viewer->rotate_viewer(value, 'x');
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  viewer->rotate_viewer(value, 'y');
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value) {
  viewer->rotate_viewer(value, 'z');
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value) {
  viewer->scale_viewer(value);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value) {
  viewer->move_viewer(value, 'x');
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value) {
  viewer->move_viewer(value, 'y');
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value) {
  viewer->move_viewer(value, 'z');
}

void MainWindow::on_radioButton_toggled() {
  viewer->projection = 1;
  viewer->update_frame();
}

void MainWindow::on_radioButton_2_toggled() {
  viewer->projection = 0;
  viewer->update_frame();
}
