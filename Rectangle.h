#pragma once
#include "Shape.h"

class MyRectangle : public Shape
{
private:
	int x, y, width, height;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	MyRectangle(int, int, int, int, const Color&, float, const Color&, float, float);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	void draw(Graphics&) override;
};

