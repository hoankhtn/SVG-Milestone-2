#include "Line.h"

Line::Line(int x1, int y1, int x2, int y2, const Color& stroke, float strokeWidth, float strokeOpacity)
    : x1(x1), y1(y1), x2(x2), y2(y2), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

int Line::getX1() const {
    return this->x1;
}

int Line::getX2() const {
    return this->x2;
}

int Line::getY1() const {
    return this->y1;
}

int Line::getY2() const {
    return this->y2;
}

Color Line::getStroke() const {
    return this->stroke;
}

float Line::getStrokeWidth() const {
    return this->strokeWidth;
}

float Line::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void Line::draw(Graphics& graphics) {}
