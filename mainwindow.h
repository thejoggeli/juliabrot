#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

class JuliaWidget;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  JuliaWidget* getRenderTarget();
  QLabel* getFPS();
  int getValue();
  double getImaginary();
  double getReal();
  int getRenderingMode();
  int getColorMode();
  void setStatusText(QString& text);
  double getQuality();
  bool resized = false;

  ~MainWindow();

 private slots:
  void on_comboBox_currentIndexChanged(int index);

 private:
  void resizeEvent(QResizeEvent* event);
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
