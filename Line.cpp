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

void Line::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color Line::getStroke() const {
    return this->stroke;
}

void Line::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float Line::getStrokeWidth() const {
    return this->strokeWidth;
}

void Line::setStrokeOpacity(float strokeOpacity) {
    this->strokeOpacity = strokeOpacity;
}

float Line::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void Line::draw(Graphics& graphics) {
    if (transform == nullptr) return;

    float sx = transform->getScale().getPointX();
    float sy = transform->getScale().getPointY();
    float tx = transform->getTranslate().getPointX();
    float ty = transform->getTranslate().getPointY();
    float rotate = transform->getRotate();

    Matrix m;
    m.Scale(sx, sy);
    m.Rotate(rotate);
    m.Translate(tx, ty);

    PointF points[2] = {
        PointF((REAL)x1, (REAL)y1),
        PointF((REAL)x2, (REAL)y2)
    };
    m.TransformPoints(points, 2);

    Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);

    graphics.DrawLine(&pen,
        points[0].X, points[0].Y,
        points[1].X, points[1].Y);
}
