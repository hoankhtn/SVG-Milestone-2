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
	void setFill(const Color&);
	Color getFill() const;
	void setFillOpacity(float);
	float getFillOpacity() const;
	void setStroke(const Color&);
	Color getStroke() const;
	void setStrokeWidth(float);
	float getStrokeWidth() const;
	void setStrokeOpacity(float);
	float getStrokeOpacity() const;
	void draw(Graphics&) override;
};

