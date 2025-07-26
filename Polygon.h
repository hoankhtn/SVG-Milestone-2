#pragma once
#include "Shape.h"
#include "Point2D.h"

class MyPolygon : public Shape
{
private:
	Color fill;
	float fillOpacity;
	vector <Point2D> pts;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	MyPolygon(const Color&, float, const vector<Point2D>&, const Color&, float , float);
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	vector<Point2D> getPoints() const;
	void draw(Graphics&) override;
};

