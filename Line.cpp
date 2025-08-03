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

void Line::draw(Graphics& graphics) {
    Point2D p1((float)x1, (float)y1);
    Point2D p2((float)x2, (float)y2);

    Point2D tp1 = transform->applyToPoint(p1);
    Point2D tp2 = transform->applyToPoint(p2);

    Color strokeColor = Color((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);

    graphics.DrawLine(&pen, (INT)tp1.getPointX(), (INT)tp1.getPointY(), (INT)tp2.getPointX(), (INT)tp2.getPointY());
}
