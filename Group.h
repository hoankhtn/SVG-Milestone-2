#pragma once
#include "Shape.h"

class Group : public Shape {
private:
	vector <Shape*> children;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	vector <Shape*> getChildren() const;
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	Group(vector <Shape*>, const Color&, float, const Color&, float, float);

	void draw(Graphics&) override;
};