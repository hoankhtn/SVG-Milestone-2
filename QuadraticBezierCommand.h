#pragma once
#include "PathCommand.h"
class QuadraticBezierCommand : public PathCommand
{
private:
	float x1, y1;
	float x, y;
	bool relative;
public:
	QuadraticBezierCommand(float, float, float, float, bool);

	//Getter declarations
	float getX1() const;
	float getY1() const;
	float getX() const;
	float getY() const;
	bool getRelative() const;

	void print(ostream&) const override;//Use for debug
	void execute(Graphics&, Pen*, Point2D&, Point2D&, char&) override;
};

