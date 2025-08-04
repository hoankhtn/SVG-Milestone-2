#include "Polygon.h"

MyPolygon::MyPolygon(const Color& fill, float fillOpacity, const vector<Point2D>& pts, const Color& stroke, float strokeWidth, float strokeOpacity)
    : fill(fill), fillOpacity(fillOpacity), pts(pts), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
}

vector<Point2D> MyPolygon::getPoints() const {
    return this->pts;
}

void MyPolygon::setFill(const Color& fill) {
    this->fill = fill;
}

Color MyPolygon::getFill() const {
    return this->fill;
}

void MyPolygon::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float MyPolygon::getFillOpacity() const {
    return this->fillOpacity;
}

void MyPolygon::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color MyPolygon::getStroke() const {
    return this->stroke;
}

void MyPolygon::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float MyPolygon::getStrokeWidth() const {
    return this->strokeWidth;
}

void MyPolygon::setStrokeOpacity(float) {
    this->strokeOpacity = strokeOpacity;
}

float MyPolygon::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyPolygon::draw(Graphics& graphics) {}


