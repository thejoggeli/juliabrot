#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDoubleSpinBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

class JuliaWidget;
class JuliaRenderer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
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
	bool exitRequested = false;
	JuliaRenderer* juliaRenderer;

	~MainWindow();

protected:

	void savePng(int w, int h);

private slots:
	void on_comboBox_currentIndexChanged(int index);
	void on_actionSave_PNG_Custom_triggered();
	void on_actionSave_PNG_1080_triggered();
	void on_actionSave_PNG_2160_triggered();
	void on_actionSave_PNG_4320_triggered();
	void on_actionSave_PNG_8640_triggered();
	void on_actionExit_triggered();

private:
	void resizeEvent(QResizeEvent* event);
	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
