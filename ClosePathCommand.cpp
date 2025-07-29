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


vvoid ClosePathCommand::execute(Graphics& g, Pen* pen, GraphicsPath* gpath, Point2D& currentPoint, Point2D& lastControlPoint, char& previousCmd) {
    // Close the current path by drawing a straight line from the current point to the starting point of the subpath.
    float currX = currentPoint.getPointX();
    float currY = currentPoint.getPointY();
    float startX = startPoint.getPointX();
    float startY = startPoint.getPointY();

    PointF pt1(currX, currY);
    PointF pt2(startX, startY);

    if (pen) g.DrawLine(pen, pt1, pt2);
    if (gpath) {
        gpath->AddLine(pt1, pt2);
        gpath->CloseFigure();
    }
    currentPoint.setPoint2D(startX, startY);
    lastControlPoint.setPoint2D(startX, startY);
}


