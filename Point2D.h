#pragma once
#include <iostream>
using namespace std;
class Point2D
{
private:
	float x, y;
public:
	Point2D(float, float);
	void setPoint2D(float, float);
	float getPointX() const;
	float getPointY() const;
};

