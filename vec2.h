#ifndef VEC2_H
#define VEC2_H
/*!
 * \brief The Vec2 class (x,y)
 */
class Vec2
{
 public:
  //! \brief x variable
  double x;
  //! \brief y variable
  double y;
  //! \brief Vec2 konstructor default, x,y = 0
  Vec2();
  //! \brief Vec2 with two parameters
  //! \param x position x
  //! \param y position y
  Vec2(double x, double y);

  //! \brief set actual Position
  //! \param x position x
  //! \param y position y
  void set(double x, double y);

  //! \brief add methode, algorith for calculate camera position
  //! \param x postion x
  //! \param y position y
  void add(double x, double y);

  //! \brief getLength Length of vector
  //! \return returning double
  double getLength();
  //! \brief getLengthSquared Squared lenght of vector
  //! \return returning double
  double getLengthSquared();
};

#endif  // VEC2_H
