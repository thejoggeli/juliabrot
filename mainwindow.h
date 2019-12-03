#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  QLabel* getRenderTarget();
  QLabel* getFPS();
  int getValue();
  double getcomplex();
  double getreel();
  int getmode();

  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_comboBox_currentIndexChanged(int index);

  void on_doubleSpinBox_3_valueChanged(double arg1);

 private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
