#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

class JuliaWidget;
class JuliaRenderer;

namespace Ui
{
class MainWindow;
}
//! \brief The MainWindow class  Mainwindow include Qmainwindow
class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  //! \brief MainWindow default construct
  //! \param parent pointer as param
  explicit MainWindow(QWidget* parent = nullptr);
  //! \brief getRenderTarget pointer refered to class JuliaWidget
  //! \return type JuliaWidget
  JuliaWidget* getRenderTarget();
  //! \brief getFPS pointer refered to class QLabel
  //! \return type getFPS
  QLabel* getFPS();
  //! \brief getValue constructor
  //! \return returning integer
  int getValue();
  //! \brief getImaginary constructor
  //! \return returning double
  double getImaginary();
  //! \brief getReal construct
  //! \return returning double
  double getReal();
  //! \brief getRenderingMode constructor
  //! \return returning integer
  int getRenderingMode();
  //! \brief getColorMode constructor
  //! \return returning integer
  int getColorMode();
  //! \brief setStatusText constructor
  //! \param text param defined as reference
  void setStatusText(QString& text);
  //! \brief getQuality constructor
  //! \return returning double
  double getQuality();
  //! \brief resized bool param initialised as false
  bool resized = false;
  //! \brief exitRequested bool param initialised as false
  bool exitRequested = false;
  //! \brief juliaRenderer pointer with class JuliaRenderer
  JuliaRenderer* juliaRenderer;

  ~MainWindow();

 protected:
  //! \brief savePng constructor
  //! \param w integer param
  //! \param h integer param
  void savePng(int w, int h);

 private slots:
  //! \brief on_comboBox_currentIndexChanged constructor
  //! \param index integer param
  void on_comboBox_currentIndexChanged(int index);
  //! \brief on_actionSave_PNG_Custom_triggered constructor
  void on_actionSave_PNG_Custom_triggered();
  //! \brief on_actionSave_PNG_1080_triggered constructor
  void on_actionSave_PNG_1080_triggered();
  //! \brief on_actionSave_PNG_2160_triggered constructor
  void on_actionSave_PNG_2160_triggered();
  //! \brief on_actionSave_PNG_4320_triggered constructor
  void on_actionSave_PNG_4320_triggered();
  //! \brief on_actionSave_PNG_8640_triggered constructor
  void on_actionSave_PNG_8640_triggered();
  //! \brief on_actionExit_triggered constructor
  void on_actionExit_triggered();

 private:
  //! \brief resizeEvent constructor
  //! \param event pointer with Qresizeevent as type
  void resizeEvent(QResizeEvent* event);
  //! \brief ui pointer param
  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
