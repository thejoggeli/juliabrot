#ifndef VEC2_H
#define VEC2_H

class Vec2
{
 public:
  double x, y;
  Vec2();
  Vec2(double x, double y);
  void set(double x, double y);
  void add(double x, double y);
  double getLength();
  double getLengthSquared();
};

#endif  // VEC2_H
