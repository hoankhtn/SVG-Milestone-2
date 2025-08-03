#pragma once
#include "Point2D.h"
#include <iostream>
using namespace std;

class MyTransform {
private:
	float translateX = 0.0;
	float translateY = 0.0;
	float scaleX = 1.0;
	float scaleY = 1.0;
	float rotateD = 0.0;
public:
	MyTransform();

	//setter
	void setTranslate(float, float);
	void setScale(float, float);
	void setUniformScale(float); // Uniform scale
	void setRotate(float);
	//getter
	Point2D getTranslate() const;
	Point2D getScale() const;
	float getRotate() const;
	//combine
	void combineWith(const MyTransform& other);
};
