#include "Circle.h"

Circle::Circle(int cx, int cy, int r, const Color& fill, float fillOpacity, const Color& stroke, float strokeWidth, float strokeOpacity)
    : cx(cx), cy(cy), r(r), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

int Circle::getCx() const {
    return this->cx;
}

int Circle::getCy() const {
    return this->cy;
}

int Circle::getR() const {
    return this->r;
}

Color Circle::getFill() const {
    return this->fill;
}

float Circle::getFillOpacity() const {
    return this->fillOpacity;
}

Color Circle::getStroke() const {
    return this->stroke;
}

float Circle::getStrokeWidth() const {
    return this->strokeWidth;
}

float Circle::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void Circle::draw(Graphics& graphics) {}
