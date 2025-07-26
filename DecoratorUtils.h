#pragma once
#include "ShapeDecorator.h"
// Utility to get the core (original) shape from a chain of decorators
Shape* getCoreShape(Shape* s);

