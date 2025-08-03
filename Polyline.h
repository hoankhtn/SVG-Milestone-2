#pragma once
#include "Shape.h"
#include "Point2D.h"

class MyPolyline : public Shape
{
private:
	Color fill;
	float fillOpacity;
	vector <Point2D> pts;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	MyPolyline(const Color&, float, const vector<POINT>&, const Color&, float, float);
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
	vector<Point2D> getPoints() const;
	void draw(Graphics&) override;
};

