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

// wird evtl. nicht benötigt
void MainWindow::on_pushButton_clicked()
{
  cout << ui->spinBox->value() << endl;
}

QLabel* MainWindow::getRenderTarget()
{
  return ui->label_7;
}

QLabel* MainWindow::getFPS()
{
  return ui->label_8;
}

int MainWindow::getValue()
{
  return ui->spinBox->value();
}

double MainWindow::getcomplex()
{
  return ui->doubleSpinBox_2->value();
}

double MainWindow::getreel()
{
  return ui->doubleSpinBox_3->value();
}

// Modus Erkennung
// Julia-set = index 0, Mandelbrot = index 1
int MainWindow::getmode()
{
  int startmodus = 0;
  int changedmodus = ui->comboBox->currentIndex();
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

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
}
