#ifndef JULIAWIDGET_H
#define JULIAWIDGET_H

#include <QWidget>
/*!
 * \brief The JuliaWidget class
 */
class JuliaWidget : public QWidget
{
  Q_OBJECT
 public:
  /*!
   * \brief JuliaWidget
   * \param parent
   */
  explicit JuliaWidget(QWidget* parent = nullptr);

  //! set the image that gets renderer to the widget panel
  //! \param image pointer to the image
  void setImage(QImage* image);

 protected:
  /*!
   * \brief paintEvent
   * \param event
   */
  void paintEvent(QPaintEvent* event);

  //! the image to draw to the panel
  QImage* image;

 signals:

 public slots:
};

#endif  // JULIAWIDGET_H
