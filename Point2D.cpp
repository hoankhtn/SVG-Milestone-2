#include "Point2D.h"

Point2D::Point2D(float x, float y) : x(x), y(y) {}

void Point2D::setPoint2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Point2D::getPointX() const { return x; }
float Point2D::getPointY() const { return y; }
