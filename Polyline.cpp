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

void MyPolyline::setFill(const Color& fill) {
    this->fill = fill;
}

Color MyPolyline::getFill() const {
    return this->fill;
}

void MyPolyline::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float MyPolyline::getFillOpacity() const {
    return this->fillOpacity;
}

void MyPolyline::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color MyPolyline::getStroke() const {
    return this->stroke;
}

void MyPolyline::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float MyPolyline::getStrokeWidth() const {
    return this->strokeWidth;
}

void MyPolyline::setStrokeOpacity(float) {
    this->strokeOpacity = strokeOpacity;
}

float MyPolyline::getStrokeOpacity() const {
    return this->strokeOpacity;
}


void MyPolyline::draw(Graphics& graphics) {
    if (!transform) return;
    if (pts.size() < 2) return;

    float sx = transform->getScale().getPointX();
    float sy = transform->getScale().getPointY();
    float tx = transform->getTranslate().getPointX();
    float ty = transform->getTranslate().getPointY();
    float rotate = transform->getRotate();

    Matrix m;
    m.Scale(sx, sy);
    m.Rotate(rotate);
    m.Translate(tx, ty);

    vector<PointF> pointsF;
    for (const auto& pt : pts) {
        pointsF.emplace_back(PointF(pt.getPointX(), pt.getPointY()));
    }
    m.TransformPoints(pointsF.data(), static_cast<INT>(pointsF.size()));

    if (strokeOpacity > 0.0f && strokeWidth > 0.0f) {
        Color strokeColor((BYTE)(strokeOpacity * 255), stroke.GetR(), stroke.GetG(), stroke.GetB());
        Pen pen(strokeColor, strokeWidth);
        graphics.DrawLines(&pen, pointsF.data(), static_cast<INT>(pointsF.size()));
    }
}
