#include "mainwindow.h"
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
  ui->label_7->setText("test ok");
}

void MainWindow::on_pushButton_clicked(bool checked)
{
}

QLabel* MainWindow::getRenderTarget()
{
  return ui->label_7;
}
