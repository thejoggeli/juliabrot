#include "mainwindow.h"
#include "iostream"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "juliarenderer.h"
#include "juliatime.h"
#include <QDir>
#include <QProgressDialog>

using namespace std;

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
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

	if (startmodus == changedmodus) {
		return startmodus;
	}

	else {
		return changedmodus;
	}
}
int MainWindow::getColorMode()
{
	int startmodus = 0;
	int changedmodus = ui->comboBox_2->currentIndex();
	if (startmodus == changedmodus)
		return startmodus;
	else {
		return changedmodus;
	}
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
	if (index == 1) {
		ui->doubleSpinBox_2->setDisabled(true);
		ui->doubleSpinBox_3->setDisabled(true);
	}

	else if (index == 0) {
		ui->doubleSpinBox_2->setDisabled(false);
		ui->doubleSpinBox_3->setDisabled(false);
	}
}

void MainWindow::on_actionExit_triggered(){
	close();
}

void MainWindow::on_actionSave_PNG_1080_triggered(){
	savePng(1920, 1080);
}

void MainWindow::on_actionSave_PNG_2160_triggered(){
	savePng(1920*2, 1080*2);
}

void MainWindow::on_actionSave_PNG_4320_triggered(){
	savePng(1920*4, 1080*4);
}

void MainWindow::on_actionSave_PNG_8640_triggered(){
	savePng(1920*8, 1080*8);
}

void MainWindow::on_actionSave_PNG_Custom_triggered(){
	QInputDialog dialog;
	dialog.setWindowTitle("Save PNG");
	dialog.setLabelText("Enter PNG dimensions (width x height)");
	dialog.setTextValue("1920x1080");
	if(!dialog.exec()){
		return;
	}
	QString result = dialog.textValue();
	QStringList split = result.split("x");
	bool valid = true;
	if(split.size() != 2) valid = false;
	int w = 0, h = 0;
	try {
		w = std::stoi(split[0].toStdString());
		h = std::stoi(split[1].toStdString());
	} catch (std::exception const& e){
		w = 0;
		h = 0;
	}
	savePng(w, h);
}


void MainWindow::savePng(int w, int h){
	if(w <= 0 || h <= 0){
		QMessageBox::critical(this, "Error", "Invalid dimensions");
		return;
	}
	QMessageBox box;
	box.setStandardButtons(QMessageBox::Ok);
	box.setWindowTitle("Save PNG");
	box.setText("Saving image, please wait ...");
	box.setIcon(QMessageBox::Information);

	QImage image = QImage(w, h, QImage::Format_ARGB32);

	double ratio = ((double)getRenderTarget()->height()/((double)h));

	juliaRenderer->render(image, 1.0/ratio);
	QString file = "export/image_";
	file += QString::number(JuliaTime::currentTimeMs);
	file += ".png";
	QDir dir;
	dir.mkdir("export");
	image.save(file);
	box.setText("Image was saved as:\n" + file);
	box.exec();
}

void MainWindow::setStatusText(QString& text)
{
	statusBar()->showMessage(text);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
	resized = true;
}

double MainWindow::getQuality()
{
	return ui->doubleSpinBox->value() * 0.01;
}

/* void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
}
*/
