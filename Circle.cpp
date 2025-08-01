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

void Circle::draw(Graphics& graphics) {
    MyTransform transform;
    transform.setTranslate(0, 0);
    transform.setRotate(0);
    transform.setUniformScale(1.0);

    Point2D center(cx, cy);
    Point2D transformedCenter = transform.applyToPoint(center);

    float sx = transform.getScale().getPointX();
    float sy = transform.getScale().getPointY();
    float scaledRadius = r * (sx + sy) / 2.0f;

    Color fillColor(static_cast<BYTE>(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
    SolidBrush brush(fillColor);

    Color strokeColor(static_cast<BYTE>(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);

    graphics.DrawEllipse(
        &pen,
        static_cast<INT>(transformedCenter.getPointX() - scaledRadius),
        static_cast<INT>(transformedCenter.getPointY() - scaledRadius),
        static_cast<INT>(2 * scaledRadius),
        static_cast<INT>(2 * scaledRadius)
    );

    graphics.FillEllipse(
        &brush,
        static_cast<INT>(transformedCenter.getPointX() - scaledRadius),
        static_cast<INT>(transformedCenter.getPointY() - scaledRadius),
        static_cast<INT>(2 * scaledRadius),
        static_cast<INT>(2 * scaledRadius)
    );
}


