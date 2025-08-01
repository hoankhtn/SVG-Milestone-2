#include "Polygon.h"

MyPolygon::MyPolygon(const Color& fill, float fillOpacity, const vector<Point2D>& pts, const Color& stroke, float strokeWidth, float strokeOpacity)
    : fill(fill), fillOpacity(fillOpacity), pts(pts), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

vector<Point2D> MyPolygon::getPoints() const {
    return this->pts;
}

Color MyPolygon::getFill() const {
    return this->fill;
}

float MyPolygon::getFillOpacity() const {
    return this->fillOpacity;
}

Color MyPolygon::getStroke() const {
    return this->stroke;
}

float MyPolygon::getStrokeWidth() const {
    return this->strokeWidth;
}

float MyPolygon::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyPolygon::draw(Graphics& graphics) {
    if (pts.size() < 3) return;

    std::vector<Point> transformedPoints;
    for (const auto& pt : pts) {
        Point2D t = transform->applyToPoint(pt);
        transformedPoints.emplace_back(Point((INT)t.getPointX(), (INT)t.getPointY()));
    }

    Color fillColor = Color((BYTE)(fillOpacity * 255), fill.GetR(), fill.GetG(), fill.GetB());
    SolidBrush brush(fillColor);
    graphics.FillPolygon(&brush, transformedPoints.data(), static_cast<INT>(transformedPoints.size()));

    Color strokeColor = Color((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
    Pen pen(strokeColor, strokeWidth);
    graphics.DrawPolygon(&pen, transformedPoints.data(), static_cast<INT>(transformedPoints.size()));
}
