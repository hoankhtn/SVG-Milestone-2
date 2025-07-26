#include "ClosePathCommand.h"
#include "Point2D.h"
ClosePathCommand::ClosePathCommand(const Point2D& startPoint) : startPoint(startPoint) {}

Point2D ClosePathCommand::getStartPoint() const {
	return startPoint;
}

void ClosePathCommand::print(std::ostream& os) const {
    os << "ClosePathCommand: startPoint = ("
        << startPoint.getPointX() << ", "
        << startPoint.getPointY() << ")\n";
}

void ClosePathCommand::execute(Graphics& g, Pen* pen, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {

}
