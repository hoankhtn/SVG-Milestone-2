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

void MyPolygon::draw(Graphics& graphics) {}