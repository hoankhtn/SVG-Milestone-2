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

void MyRectangle::draw(Graphics& graphics) {
    Point2D p1(x, y);
    Point2D p2(x + width, y);
    Point2D p3(x + width, y + height);
    Point2D p4(x, y + height);

    Point2D tp1 = transform->applyToPoint(p1);
    Point2D tp2 = transform->applyToPoint(p2);
    Point2D tp3 = transform->applyToPoint(p3);
    Point2D tp4 = transform->applyToPoint(p4);

    Point points[4] = {
        Point((INT)tp1.getPointX(), (INT)tp1.getPointY()),
        Point((INT)tp2.getPointX(), (INT)tp2.getPointY()),
        Point((INT)tp3.getPointX(), (INT)tp3.getPointY()),
        Point((INT)tp4.getPointX(), (INT)tp4.getPointY())
    };

    Color fillColor = Color((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
    SolidBrush brush(fillColor);
    graphics.FillPolygon(&brush, points, 4);

    Color strokeColor = Color((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);
    graphics.DrawPolygon(&pen, points, 4);
}
