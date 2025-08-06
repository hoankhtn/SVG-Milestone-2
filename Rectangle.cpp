#include "Rectangle.h"

MyRectangle::MyRectangle(int x, int y, int width, int height, const Color& fill, float fillOpacity, const Color& stroke, float strokeWidth, float strokeOpacity, MyTransform* rectTransform)
    : x(x), y(y), width(width), height(height), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
    transform = rectTransform;
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

void MyRectangle::setFill(const Color& fill) {
    this->fill = fill;
}

Color MyRectangle::getFill() const {
    return this->fill;
}

void MyRectangle::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float MyRectangle::getFillOpacity() const {
    return this->fillOpacity;
}

void MyRectangle::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color MyRectangle::getStroke() const {
    return this->stroke;
}

void MyRectangle::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float MyRectangle::getStrokeWidth() const {
    return this->strokeWidth;
}

void MyRectangle::setStrokeOpacity(float) {
    this->strokeOpacity = strokeOpacity;
}

float MyRectangle::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyRectangle::draw(Graphics& graphics) {}

