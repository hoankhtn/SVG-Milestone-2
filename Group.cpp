#include "Group.h"
#include "Shapes.h"

Group::Group(vector<Shape*> children,
    const Color& fill, float fillOpacity,
    const Color& stroke, float strokeWidth, float strokeOpacity, int fontSize, MyTransform* groupTransform)
{
    this->children.clear();
    for (auto* child : children) {
        if (child) {
            this->children.push_back(child);
        }
	}
    this->fill = fill;
    this->fillOpacity = fillOpacity;
    this->stroke = stroke;
    this->strokeWidth = strokeWidth;
    this->strokeOpacity = strokeOpacity;
    this->fontSize = fontSize;

    transform = groupTransform;
}

vector<Shape*> Group::getChildren() const {
    return children;
}

void Group::setFill(const Color& fill) {
    this->fill = fill;
}

Color Group::getFill() const {
    return fill;
}

void Group::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float Group::getFillOpacity() const {
    return fillOpacity;
}

void Group::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color Group::getStroke() const {
    return stroke;
}

void Group::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float Group::getStrokeWidth() const {
    return strokeWidth;
}

void Group::setStrokeOpacity(float strokeOpacity) {
    this->strokeOpacity = strokeOpacity;
}

float Group::getStrokeOpacity() const {
    return strokeOpacity;
}

int Group::getFontSize() const {
    return fontSize;
}

void Group::draw(Graphics& graphics) {}

