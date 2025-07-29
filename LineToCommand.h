#pragma once
#include "PathCommand.h"
class LineToCommand : public PathCommand
{
private:
	float x, y;
	bool relative;
public:
	LineToCommand(float, float, bool);

	//Getter declarations
	float getX() const;
	float getY() const;
	bool getRelative() const;

	void print(ostream&) const override;
	void execute(Graphics&, Pen*, GraphicsPath*, Point2D&, Point2D&, char&) override;
};


