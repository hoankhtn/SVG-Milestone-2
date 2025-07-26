#pragma once
#include "Shape.h"
#include "Point2D.h"
#include "PathCommand.h"
#include "Group.h"
class ReadFileSVG
{
private:
	string fileName;
public:
	ReadFileSVG(const string&);
	Color parseColor(const char*, float);
	float parseFloat(const char* s, float);
	int parseInt(const char* s, int);
	vector<Point2D> parsePoints(const char*);
	bool isLetter(char c);
	vector <string> splitPathCommands(const string&);
	vector <float> parseNumbers(const string&);
	vector <PathCommand*> parseCommands(const vector <string>&);
	Shape* parsePath(xml_node<>*);
	Shape* parseLine(xml_node<>*);
	Shape* parseCircle(xml_node<>*);
	Shape* parseEllipse(xml_node<>*);
	Shape* parseRectangle(xml_node<>*);
	Shape* parsePolyline(xml_node<>*);
	Shape* parsePolygon(xml_node<>*);
	Shape* parseText(xml_node<>*);
	Shape* parseGroup(xml_node<>*);
	~ReadFileSVG();
};

