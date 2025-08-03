#include "Group.h"

Group::Group(vector<Shape*> children,
    const Color& fill, float fillOpacity,
    const Color& stroke, float strokeWidth, float strokeOpacity, int fontSize)
{
    this->children = children;
    this->fill = fill;
    this->fillOpacity = fillOpacity;
    this->stroke = stroke;
    this->strokeWidth = strokeWidth;
    this->strokeOpacity = strokeOpacity;
    this->fontSize = fontSize;
}

vector<Shape*> Group::getChildren() const {
    return children;
}

Color Group::getFill() const {
    return fill;
}

float Group::getFillOpacity() const {
    return fillOpacity;
}

Color Group::getStroke() const {
    return stroke;
}

float Group::getStrokeWidth() const {
    return strokeWidth;
}

float Group::getStrokeOpacity() const {
    return strokeOpacity;
}

int Group::getFontSize() const {
    return fontSize;
}

void Group::draw(Graphics& g) {
    if (transform == nullptr) return;

    for (Shape* subShape : children) {
        if (!subShape) continue;

        MyTransform* groupTransform = this->getTransform();
        MyTransform* shapeTransform = subShape->getTransform();

        if (groupTransform && shapeTransform) {
            MyTransform* combined = new MyTransform(*shapeTransform);
            combined->combineWith(*groupTransform);
            subShape->setTransform(combined);
        }

        subShape->draw(g);
    }
}

