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
	MyEllipse(int, int, int, int, const Color&, float, const Color&, float, float);
	void draw(Graphics&) override;
};

