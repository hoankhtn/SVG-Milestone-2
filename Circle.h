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
	Circle(int, int, int, const Color&, float, const Color&, float, float, MyTransform*);
	void draw(Graphics&) override;
};

