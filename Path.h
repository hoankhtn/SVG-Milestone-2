#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Shape.h"
#include "PathCommand.h"
class Path : public Shape
{
private:
	vector<PathCommand*> commands;
	Color fill;
	float fillOpacity;
	Color stroke;
	float strokeWidth;
	float strokeOpacity;
public:
	Path(const vector<PathCommand*>&, Color, float, Color, float, float);
	vector<PathCommand*> getCommands() const;
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

	~Path();
};

