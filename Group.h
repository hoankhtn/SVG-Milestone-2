#pragma once
#include "MyTransform.h"
#include "Shape.h"

class Group : public Shape {
private:
	vector <Shape*> children;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
	int fontSize;
public:
	vector <Shape*> getChildren() const;
	Color getFill() const;
	float getFillOpacity() const;
	Color getStroke() const;
	float getStrokeWidth() const;
	float getStrokeOpacity() const;
	int getFontSize() const;
	Group(vector <Shape*>, const Color&, float, const Color&, float, float, int);

	void draw(Graphics&) override;
};