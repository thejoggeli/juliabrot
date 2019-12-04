#include "vec2.h"

Vec2::Vec2()
{
}

Vec2::Vec2(double x, double y) : x(x), y(y)
{
}

void Vec2::set(double x, double y)
{
  this->x = x;
  this->y = y;
}

void Vec2::add(double x, double y)
{
  this->x += x;
  this->y += y;
}
