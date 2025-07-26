#include "Polyline.h"

MyPolyline::MyPolyline(const Color& fill, float fillOpacity, const std::vector<POINT>& pts, const Color& stroke, float strokeWidth, float strokeOpacity)
    : fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity)
{
    for (const POINT& p : pts) {
        this->pts.emplace_back(Point2D(static_cast<float>(p.x), static_cast<float>(p.y)));
    }
}

vector<Point2D> MyPolyline::getPoints() const {
    return this->pts;
}

Color MyPolyline::getFill() const {
    return this->fill;
}

float MyPolyline::getFillOpacity() const {
    return this->fillOpacity;
}

Color MyPolyline::getStroke() const {
    return this->stroke;
}

float MyPolyline::getStrokeWidth() const {
    return this->strokeWidth;
}

float MyPolyline::getStrokeOpacity() const {
    return this->strokeOpacity;
}

void MyPolyline::draw(Graphics& graphics) {}
