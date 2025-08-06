#pragma once
#include "Shape.h"

class Line : public Shape
{
	int x1, y1, x2, y2;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	Line(int, int, int, int, const Color&, float, float, MyTransform*);
	int getX1() const;
	int getX2() const;
	int getY1() const;
	int getY2() const;
	void setStroke(const Color&);
	Color getStroke() const;
	void setStrokeWidth(float);
	float getStrokeWidth() const;
	void setStrokeOpacity(float);
	float getStrokeOpacity() const;
	void draw(Graphics&) override;
};

