#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

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
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_clicked(bool checked);

 private:
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
