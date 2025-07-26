#pragma once
#include "Shape.h"

class MyEllipse : public Shape
{
private:
	int cx, cy, rx, ry;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	int getCx() const;
	int getCy() const;
	int getRx() const;
	int getRy() const;
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	MyEllipse(int, int, int, int, const Color&, float, const Color&, float, float);
	void draw(Graphics&) override;
};

