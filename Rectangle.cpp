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

void MyRectangle::draw(Graphics& graphics) {
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

    PointF points[4] = {
        PointF((REAL)x, (REAL)y),
        PointF((REAL)(x + width), (REAL)y),
        PointF((REAL)(x + width), (REAL)(y + height)),
        PointF((REAL)x, (REAL)(y + height))
    };

    m.TransformPoints(points, 4);

    if (fillOpacity > 0.0f) {
        Color fillColor((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
        SolidBrush brush(fillColor);
        graphics.FillPolygon(&brush, points, 4);
    }

    if (strokeOpacity > 0.0f && strokeWidth > 0.0f) {
        Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawPolygon(&pen, points, 4);
    }
}
