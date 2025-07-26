#include "DecoratorUtils.h"
//Implement
Shape* getCoreShape(Shape* s) {
    while (auto dec = dynamic_cast<ShapeDecorator*>(s)) {
        s = dec->getWrappedShape();
    }
    return s;
}