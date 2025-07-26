#pragma once
#include "Shape.h"
// Abstract base class for shape decorators
class ShapeDecorator : public Shape
{
protected:
	Shape* shape; // Pointer to the shape being decorated
public:
	ShapeDecorator(Shape*);
	Shape* getWrappedShape() const;
	virtual void draw(Graphics&) override = 0; // Must be implemented by derived decorators
	virtual ~ShapeDecorator() {};
};

