#pragma once
#include "ShapeDecorator.h"
// Decorator for adding background fill to a shape
class BackgroundDecorator : public ShapeDecorator
{
public:
	BackgroundDecorator(Shape*);
	void draw(Graphics&) override; // Draws the background fill and then the original shape
};

