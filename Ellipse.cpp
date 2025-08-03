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

void MyEllipse::setFill(const Color& fill) {
    this->fill = fill;
}

Color MyEllipse::getFill() const {
    return this->fill;
}

void MyEllipse::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float MyEllipse::getFillOpacity() const {
    return this->fillOpacity;
}

void MyEllipse::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color MyEllipse::getStroke() const {
    return this->stroke;
}

void MyEllipse::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float MyEllipse::getStrokeWidth() const {
    return this->strokeWidth;
}

void MyEllipse::setStrokeOpacity(float strokeOpacity) {
    this->strokeOpacity = strokeOpacity;
}

float MyEllipse::getStrokeOpacity() const {
    return this->strokeOpacity;
}


void MyEllipse::draw(Graphics& graphics) {
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

    PointF center((REAL)(cx), (REAL)(cy));
    m.TransformPoints(&center, 1);

    float scaledRx = rx * sx;
    float scaledRy = ry * sy;

    Color fillColor((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
    SolidBrush fillBrush(fillColor);
    graphics.FillEllipse(&fillBrush,
        center.X - scaledRx, center.Y - scaledRy,
        2 * scaledRx, 2 * scaledRy);

    Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen strokePen(strokeColor, strokeWidth);
    graphics.DrawEllipse(&strokePen,
        center.X - scaledRx, center.Y - scaledRy,
        2 * scaledRx, 2 * scaledRy);
}

