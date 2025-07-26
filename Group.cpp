#include "Group.h"

Group::Group(vector<Shape*> children,
    const Color& fill, float fillOpacity,
    const Color& stroke, float strokeWidth, float strokeOpacity)
{
    this->children = children;
    this->fill = fill;
    this->fillOpacity = fillOpacity;
    this->stroke = stroke;
    this->strokeWidth = strokeWidth;
    this->strokeOpacity = strokeOpacity;
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

void Group::draw(Graphics& g) {


    for (Shape* shape : children) {
        if (shape) {
            shape->draw(g);
        }
    }
}

