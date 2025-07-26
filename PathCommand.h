#pragma once
#include "Resource.h"
#include "Point2D.h"
class PathCommand
{
public:
	virtual void execute(Graphics&, Pen*, Point2D&, Point2D&, char&) = 0;
	virtual void print(ostream&) const = 0; // Use for debug
	virtual ~PathCommand() {};
};

