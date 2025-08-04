#pragma once
#include "Resource.h"

class MyTransform {
private:
	Matrix* matrix;
public:
	MyTransform();
	//Copy constructor
	MyTransform(const MyTransform&);
	//setter
	MyTransform& operator=(const MyTransform& other); // Copy assignment
	~MyTransform(); // Destructor
	void setTranslate(float, float);
	void setScale(float, float);
	void setUniformScale(float); // Uniform scale
	void setRotate(float);
	//combine
	void combineWith(MyTransform*);
	//get Matrix
	const Matrix& getMatrix() const;
	//apply
	void applyTo(Graphics&) const;
	MyTransform* clone() const;
};
