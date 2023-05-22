
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

  connect(viewer, SIGNAL(change_rotation(int, char)), this,
          SLOT(change_slider_position(int, char)));

  loadSettings();

  view = (QWidget *)(viewer);
  layout->addWidget(view);
  ui->openGLWidget->setLayout(layout);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
  ui->horizontalLayoutWidget->resize(this->size());
}

void MainWindow::loadSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

  ui->radioButton->setChecked(settings.value("Parallel", false).toBool());
  ui->radioButton_2->setChecked(settings.value("Central", false).toBool());

  viewer->base_scale = 1;
  ui->horizontalSlider_4->setValue(
      (settings.value("Scale", 1.00).toDouble() - 1) * 100);
  ui->horizontalSlider_8->setValue(settings.value("LineWidth", 1).toInt());
}

void MainWindow::saveSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  settings.setValue("Parallel", ui->radioButton->isChecked());
  settings.setValue("Central", ui->radioButton_2->isChecked());
  settings.setValue("Scale",
                    (1 + ((double)ui->horizontalSlider_4->value() / 100)));

  settings.setValue("LineWidth", ui->horizontalSlider_8->value());
  settings.sync();
}
MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
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
  if (dir == 'x') ui->horizontalSlider->setValue(degrees);
  if (dir == 'y') ui->horizontalSlider_2->setValue(degrees);
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
  viewer->new_scale = 1 + (double)value / 100;
  viewer->scale_viewer(viewer->new_scale);
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

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
  viewer->change_line_width(value);
}

