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
	int getFontSize() const;
	Group(vector <Shape*>, const Color&, float, const Color&, float, float, int);

	void draw(Graphics&) override;
};