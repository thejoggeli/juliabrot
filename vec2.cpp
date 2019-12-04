#include "vec2.h"
#include <cmath>

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

double Vec2::getLength(){
	return sqrt(x*x+y*y);
}
double Vec2::getLengthSquared(){
	return x*x+y*y;
}
