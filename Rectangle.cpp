#include "Rectangle.h"

MyRectangle::MyRectangle(int x, int y, int width, int height, const Color& fill, float fillOpacity, const Color& stroke, float strokeWidth, float strokeOpacity)
    : x(x), y(y), width(width), height(height), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

int MyRectangle::getX() const {
    return this->x;
}

int MyRectangle::getY() const {
    return this->y;
}

int MyRectangle::getWidth() const {
    return this->width;
}

int MyRectangle::getHeight() const {
    return this->height;
}

Color MyRectangle::getFill() const {
    return this->fill;
}

float MyRectangle::getFillOpacity() const {
    return this->fillOpacity;
}

Color MyRectangle::getStroke() const {
    return this->stroke;
}

float MyRectangle::getStrokeWidth() const {
    return this->strokeWidth;
}

float MyRectangle::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyRectangle::draw(Graphics& graphics) {}
