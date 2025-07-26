#include "Path.h"

Path::Path(const vector<PathCommand*>& commands, Color fill, float fillOpacity, Color stroke, float strokeWidth, float strokeOpacity)
: commands(commands), fill(fill), fillOpacity(fillOpacity), stroke(stroke), strokeWidth(strokeWidth), strokeOpacity(strokeOpacity) {}

void Path::draw(Graphics&) {}

vector<PathCommand*> Path::getCommands() const {
	return commands;
}

Color Path::getFill() const {
	return fill;
}

float Path::getFillOpacity() const {
	return fillOpacity;
}

Color Path::getStroke() const {
	return stroke;
}

float Path::getStrokeWidth() const {
	return strokeWidth;
}

float Path::getStrokeOpacity() const {
	return strokeOpacity;
}

Path::~Path() {
	vector<PathCommand*> commands;
	for (const auto& cmds : commands) {
		delete cmds;
	}
	fillOpacity = 0.0;
	strokeWidth = 0.0;
	strokeOpacity = 0.0;
}