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
  //  int wert = ui->spinBox->value();
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
