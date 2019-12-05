#include "mainwindow.h"
#include "iostream"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

JuliaWidget* MainWindow::getRenderTarget()
{
  return ui->julia_widget;
}

int MainWindow::getValue()
{
  return ui->spinBox->value();
}

double MainWindow::getImaginary()
{
  return ui->doubleSpinBox_2->value();
}

double MainWindow::getReal()
{
  return ui->doubleSpinBox_3->value();
}

// Modus Erkennung
// Julia-set = index 0, Mandelbrot = index 1
int MainWindow::getRenderingMode()
{
  int startmodus = 0;
  int changedmodus = ui->comboBox->currentIndex();

  if (startmodus == changedmodus)
  {
    return startmodus;
  }

  else
  {
    return changedmodus;
  }
}
int MainWindow::getColorMode()
{
  int startmodus = 0;
  int changedmodus = ui->comboBox_2->currentIndex();
  if (startmodus == changedmodus)
    return startmodus;
  else
  {
    return changedmodus;
  }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  if (index == 1)
  {
    ui->doubleSpinBox_2->setDisabled(true);
    ui->doubleSpinBox_3->setDisabled(true);
  }

  else if (index == 0)
  {
    ui->doubleSpinBox_2->setDisabled(false);
    ui->doubleSpinBox_3->setDisabled(false);
  }
}

void MainWindow::setStatusText(QString& text)
{
  statusBar()->showMessage(text);
}

/* void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
}
*/
