#pragma once
#include "ShapeDecorator.h"
// Decorator for drawing text on top of a shape
class TextDecorator :  public ShapeDecorator
{
private:
	wstring text;
	int x, y;
	Color color;
	int FontSize;
public:
	TextDecorator(Shape*, wstring, int, int, const Color&, int);
	void draw(Graphics&) override; // Draws the original shape and then the text
};

