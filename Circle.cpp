#include "Circle.h"
#include "ReadFileSVG.h"

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

void Circle::setFill(const Color& fill) {
    this->fill = fill;
}

Color Circle::getFill() const {
    return this->fill;
}

void Circle::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float Circle::getFillOpacity() const {
    return this->fillOpacity;
}

void Circle::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color Circle::getStroke() const {
    return this->stroke;
}

void Circle::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float Circle::getStrokeWidth() const {
    return this->strokeWidth;
}

void Circle::setStrokeOpacity(float strokeOpacity) {
    this->strokeOpacity = strokeOpacity;
}

float Circle::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void Circle::draw(Graphics& graphics) {
    if (!transform) return;

    float sx = transform->getScale().getPointX();
    float sy = transform->getScale().getPointY();
    float tx = transform->getTranslate().getPointX();
    float ty = transform->getTranslate().getPointY();
    float rotate = transform->getRotate();

    Matrix m;
    m.Scale(sx, sy);
    m.Rotate(rotate);
    m.Translate(tx, ty);

    PointF center((REAL)cx, (REAL)cy);
    m.TransformPoints(&center, 1);

    float scaledR = r * ((sx + sy) / 2.0f);

    SolidBrush fillBrush(Color((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB()));
    graphics.FillEllipse(&fillBrush,
        center.X - scaledR, center.Y - scaledR,
        2 * scaledR, 2 * scaledR);

    Pen strokePen(Color((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB()), strokeWidth);
    graphics.DrawEllipse(&strokePen,
        center.X - scaledR, center.Y - scaledR,
        2 * scaledR, 2 * scaledR);
}



