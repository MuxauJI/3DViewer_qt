
#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  this->setWindowTitle(APPLICATION_NAME);


  layout = new QGridLayout();
  viewer = new Object_viewer();

  loadSettings();

  view = (QWidget *)(viewer);
  layout->addWidget(view);
  ui->openGLWidget->setLayout(layout);

  //connect(this, &viewer::mouseMoveEvent, r, SLOT(&MainWindow::on_horizontalSlider_valueChanged()));
}

void MainWindow::loadSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

  ui->radioButton->setChecked(settings.value("Parallel", false).toBool());
  ui->radioButton_2->setChecked(settings.value("Central", false).toBool());

  viewer->base_scale = 1;
  ui->horizontalSlider_4->setValue((settings.value("Scale", 1.00).toDouble() - 1) * 100);

}

void MainWindow::saveSettings() {
  QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
  settings.setValue("Parallel", ui->radioButton->isChecked());
  settings.setValue("Central", ui->radioButton_2->isChecked());
  settings.setValue("Scale", (1 + ((double)ui->horizontalSlider_4->value() / 100)));

  settings.sync();
}
MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  saveSettings(); //  сохраняем настройки перед открытием файла
  QString fileName_open;
  fileName_open =
      QFileDialog::getOpenFileName(this, "Open file ...", "~/", "*.obj",
                                   nullptr, QFileDialog::DontUseNativeDialog);
  if (fileName_open.isNull()) {
    return;
  } else {
    QByteArray tmp = fileName_open.toLocal8Bit();
    viewer->filename_open = tmp.data();
    loadSettings(); //  загружаем ранее сохраненные настройки для нового файла
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
