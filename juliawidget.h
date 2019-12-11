#ifndef JULIAWIDGET_H
#define JULIAWIDGET_H

#include <QWidget>

class JuliaWidget : public QWidget
{
	Q_OBJECT
public:
	explicit JuliaWidget(QWidget *parent = nullptr);
	void setImage(QImage* image);

protected:
	void paintEvent(QPaintEvent *event);
	QImage* image;

signals:

public slots:
};

#endif // JULIAWIDGET_H
