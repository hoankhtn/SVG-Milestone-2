#pragma once
#include "PathCommand.h"

class SmoothQuadraticCommand : public PathCommand
{
private:
	float x, y;
	bool relative;
public:
	SmoothQuadraticCommand(float, float, bool);

	//Getter declarations
	float getX() const;
	float getY() const;
	bool getRelative() const;

	void print(ostream&) const override;//Use for debug
	void execute(Graphics&, Pen*, GraphicsPath*, Point2D&, Point2D&, char&) override;
};

