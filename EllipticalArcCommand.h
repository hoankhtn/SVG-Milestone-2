#pragma once
#include "PathCommand.h"
class EllipticalArcCommand : public PathCommand
{
private:
	float rx, ry;
	float xAxisRotation;
	bool largeArc;
	bool sweep;
	float x, y;
	bool relative;
public:
	EllipticalArcCommand(float, float, float, bool, bool, float, float, bool);

	// Getter declarations
	float getRx() const;
	float getRy() const;
	float getXAxisRotation() const;
	bool getLargeArc() const;
	bool getSweep() const;
	float getX() const;
	float getY() const;
	bool getRelative() const;

	void print(ostream&) const override;//Use for debug
	void execute(Graphics&, Pen* pen, GraphicsPath*, Point2D&, Point2D&, char&) override;
};

