#include "ShapeDecorator.h"

ShapeDecorator::ShapeDecorator(Shape* shape) : shape(shape) {}
Shape* ShapeDecorator::getWrappedShape() const {
	return shape;
}