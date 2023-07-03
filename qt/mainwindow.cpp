
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);

  ui->horizontalLayoutWidget->resize(this->size());
  this->setWindowTitle(APPLICATION_NAME);

  layout = new QGridLayout();
  viewer = new Object_viewer();

  connect(viewer, SIGNAL(change_rotation(int,char)), this,
          SLOT(change_slider_position(int,char)));

  loadSettings();

  view = (QWidget *)(viewer);
  layout->addWidget(view);
  ui->openGLWidget->setLayout(layout);
}

void MainWindow::resizeEvent(QResizeEvent *) {
  ui->horizontalLayoutWidget->resize(this->size());
}

void MainWindow::loadSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

  ui->parallel_rbutton->setChecked(settings.value("Parallel", false).toBool());
  ui->central_rbutton->setChecked(settings.value("Central", false).toBool());

  viewer->base_scale = 1;
  ui->scale_slider->setValue(
      (settings.value("Scale", 1.00).toDouble() - 1) * 100);
  ui->line_w_slider->setValue(settings.value("LineWidth", 1).toInt());
}

void MainWindow::saveSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  settings.setValue("Parallel", ui->parallel_rbutton->isChecked());
  settings.setValue("Central", ui->central_rbutton->isChecked());
  settings.setValue("Scale",
                    (1 + ((double)ui->scale_slider->value() / 100)));

  settings.setValue("LineWidth", ui->line_w_slider->value());
  settings.sync();
}
MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_open_button_clicked() {
  saveSettings();  //  сохраняем настройки перед открытием файла
  QString fileName_open;
  fileName_open =
      QFileDialog::getOpenFileName(this, "Open file ...", "~/", "*.obj",
                                   nullptr, QFileDialog::DontUseNativeDialog);
  if (fileName_open.isNull()) {
    return;
  } else {
    QByteArray tmp = fileName_open.toLocal8Bit();
    viewer->filename_open = tmp.data();
    loadSettings();  //  загружаем ранее сохраненные настройки для нового файла
    viewer->init_facets();
  }
}

void MainWindow::change_slider_position(int val, char dir) {
  int degrees = val % 360 + (val < 0 ? 360 : 0);
  // qDebug() << degrees;
  if (dir == 'x') ui->rotation_x_slider->setValue(degrees);
  if (dir == 'y') ui->rotation_y_slider->setValue(degrees);
}

void MainWindow::on_rotation_x_slider_valueChanged(int value) {
  viewer->rotate_viewer(value, 'x');
}

void MainWindow::on_rotation_y_slider_valueChanged(int value) {
  viewer->rotate_viewer(value, 'y');
}

void MainWindow::on_rotation_z_slider_valueChanged(int value) {
  viewer->rotate_viewer(value, 'z');
}

void MainWindow::on_scale_slider_valueChanged(int value) {
  viewer->new_scale = 1 + (double)value / 100;
  viewer->scale_viewer(viewer->new_scale);
}

void MainWindow::on_move_x_slider_valueChanged(int value) {
  viewer->move_viewer(value, 'x');
}

void MainWindow::on_move_y_slider_valueChanged(int value) {
  viewer->move_viewer(value, 'y');
}

void MainWindow::on_move_z_slider_valueChanged(int value) {
  viewer->move_viewer(value, 'z');
}

void MainWindow::on_parallel_rbutton_toggled() {
  viewer->projection = 1;
  viewer->update_frame();
}

void MainWindow::on_central_rbutton_toggled() {
  viewer->projection = 0;
  viewer->update_frame();
}

void MainWindow::on_line_w_slider_valueChanged(int value) {
  viewer->change_line_width(value);
}
