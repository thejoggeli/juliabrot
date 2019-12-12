#ifndef CAMERA_H
#define CAMERA_H

#include "vec2.h"

//! \brief The Camera class
class Camera
{
 public:
  //! \brief position variable with datatype vec2
  Vec2 position;
  //! \brief zoom variable with type double
  double zoom;
  //! \brief zoom variable with type double
  double rotation;
  //! \brief Camera constructor
  Camera();
};

#endif  // CAMERA_H
