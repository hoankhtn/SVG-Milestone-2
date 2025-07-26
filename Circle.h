#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	int cx, cy, r;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	int getCx() const;
	int getCy() const;
	int getR() const;
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	Circle(int, int, int, const Color&, float, const Color&, float, float);
	void draw(Graphics&) override;
};

