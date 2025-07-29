#pragma once
#include "PathCommand.h"
class ClosePathCommand : public PathCommand
{
private:
	Point2D startPoint;
public:
	ClosePathCommand(const Point2D&);

	// Getter declarations
	Point2D getStartPoint() const;
	void print(ostream&) const override;//Use for debug
	void execute(Graphics&, Pen*, GraphicsPath*, Point2D&, Point2D&, char&) override;
};

