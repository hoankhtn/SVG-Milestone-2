#include "Path.h"
#include "Commands.h"

Path::Path(const vector<PathCommand*>& commands, Color fill, float fillOpacity, Color stroke, float strokeWidth, float strokeOpacity, MyTransform* pathTransform)
: commands(commands), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity) {}

vector<PathCommand*> Path::getCommands() const {
	return commands;
}

void Path::setFill(const Color& fill) {
    this->fill = fill;
}

Color Path::getFill() const {
	return fill;
}

void Path::setFillOpacity(float fillOpacity) {
    this->fillOpacity = fillOpacity;
}

float Path::getFillOpacity() const {
	return fillOpacity;
}

void Path::setStroke(const Color& stroke) {
    this->stroke = stroke;
}

Color Path::getStroke() const {
	return stroke;
}

void Path::setStrokeWidth(float strokeWidth) {
    this->strokeWidth = strokeWidth;
}

float Path::getStrokeWidth() const {
	return strokeWidth;
}

void Path::setStrokeOpacity(float strokeOpacity) {
    this->strokeOpacity = strokeOpacity;
}

float Path::getStrokeOpacity() const {
	return strokeOpacity;
}

void Path::draw(Graphics& graphics) {}

Path::~Path() {
    for (PathCommand* cmd : commands) {
        delete cmd;
    }
}