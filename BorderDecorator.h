#pragma once
#include "ShapeDecorator.h"
// Decorator for adding border/stroke to a shape
class BorderDecorator : public ShapeDecorator
{
public:
	BorderDecorator(Shape*);
	void draw(Graphics&) override; // Draws the border and then the original shape
};

