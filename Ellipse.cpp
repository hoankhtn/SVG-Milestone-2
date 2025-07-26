#include "Ellipse.h"
#include "Circle.h"

MyEllipse::MyEllipse(int cx, int cy, int rx, int ry, const Color& fill, float fillOpacity, const Color& stroke, float strokeWidth, float strokeOpacity)
    : cx(cx), cy(cy), rx(rx), ry(ry), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

int MyEllipse::getCx() const {
    return this->cx;
}

int MyEllipse::getCy() const {
    return this->cy;
}

int MyEllipse::getRx() const {
    return this->rx;
}

int MyEllipse::getRy() const {
    return this->ry;
}

Color MyEllipse::getFill() const {
    return this->fill;
}

float MyEllipse::getFillOpacity() const {
    return this->fillOpacity;
}

Color MyEllipse::getStroke() const {
    return this->stroke;
}

float MyEllipse::getStrokeWidth() const {
    return this->strokeWidth;
}

float MyEllipse::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyEllipse::draw(Graphics& graphics) {}
