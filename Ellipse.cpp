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

Color MyEllipse::getFill() const {
    return this->fill;
}

float MyEllipse::getFillOpacity() const {
    return this->fillOpacity;
}

Color MyEllipse::getStroke() const {
    return this->stroke;
}

float MyEllipse::getStrokeWidth() const {
    return this->strokeWidth;
}

float MyEllipse::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyEllipse::draw(Graphics& graphics) {
    const int NUM_SEGMENTS = 60;

    std::vector<Point> transformedPoints;
    float centerX = static_cast<float>(cx);
    float centerY = static_cast<float>(cy);
    float radiusX = static_cast<float>(rx);
    float radiusY = static_cast<float>(ry);

    for (int i = 0; i < NUM_SEGMENTS; ++i) {
        float theta = (2.0f * 3.14159265f * i) / NUM_SEGMENTS;
        float x = centerX + radiusX * cosf(theta);
        float y = centerY + radiusY * sinf(theta);

        Point2D original(x, y);
        Point2D transformed = transform->applyToPoint(original);
        transformedPoints.emplace_back(Point((INT)transformed.getPointX(), (INT)transformed.getPointY()));
    }

    Color fillColor((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
    SolidBrush brush(fillColor);
    graphics.FillPolygon(&brush, transformedPoints.data(), NUM_SEGMENTS);

    Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);
    graphics.DrawPolygon(&pen, transformedPoints.data(), NUM_SEGMENTS);
}
