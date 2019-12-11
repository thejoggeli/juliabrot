#include "juliawidget.h"
#include <QPainter>
#include "juliatime.h"
#include "colorhsl.h"
#include <cmath>

JuliaWidget::JuliaWidget(QWidget *parent) : QWidget(parent)
{

}

void JuliaWidget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	double image_w = image->width();
	double image_h = image->height();
	double image_aspect = image_w/image_h;

	double widget_w = this->width();
	double widget_h = this->height();
	double widget_aspect = widget_w/widget_h;

	double x, y, w, h;

	if(widget_aspect < image_aspect){
		w = widget_w;
		h = widget_w/image_aspect;
		x = 0;
		y = -(h-widget_h)/2;
	} else {
		w = widget_h*image_aspect;
		h = widget_h;
		x = -(w-widget_w)/2;
		y = 0;
	}

	QRect target = QRect(x, y, w, h);
	painter.drawImage(target, *image);

	if(!this->hasFocus()){
		double hue = 60.0/360.0;
		double sat = 1.0;
		double light = 0.7 + sin(JuliaTime::sinceStart*2)*0.2;
		QRgb rgb = ColorHsl::GetRgbUint32(hue, sat, light);
		QPen pen = QPen(rgb);
		QFont font = QFont("Arial", 14, QFont::Bold);
		painter.setFont(font);
		painter.setPen(pen);
		QFontMetrics fm(font);
		QString text = "CLICK TO FOCUS";
		painter.save();
		painter.translate(this->width()/2, this->height()*0.98-fm.height());
	//	painter.rotate(sin(JuliaTime::sinceStart)*15);
		double scale = sin(JuliaTime::sinceStart)*0.2+1.2;
		painter.scale(scale, scale);
		painter.drawText(-fm.width(text)/2, fm.height()/2, text);
		painter.restore();

	}

}

void JuliaWidget::setImage(QImage *image){
	this->image = image;
}
