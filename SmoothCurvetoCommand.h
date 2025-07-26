#pragma once
#include "PathCommand.h"

class SmoothCurvetoCommand : public PathCommand
{
private:
	//continue command C
	float x2, y2;
	float x, y;
	bool relative;
public:
	SmoothCurvetoCommand(float, float, float, float, bool);

	//Getter declaration
	float getX2() const;
	float getY2() const;
	float getX() const;
	float getY() const;
	bool getRelative() const;

	void print(ostream&) const override;//Use for debug
	void execute(Graphics&, Pen*, Point2D&, Point2D&, char&) override;
};

