#pragma once
#include <math.h>

class Vector2D									//2D Vector
{
public:
	float m_x;									//2 points in space (floats)
	float m_y;

	Vector2D();									//Default constructor
	Vector2D(float x, float y);					//Takes in two floating point numbers
	float dot(Vector2D other);					//Dot product calculator
	float magnitude();							//Magnitude calculator
	void normalise();							//Normalize function
												//void print();								//Prints to console in x, y format
	Vector2D operator + (Vector2D other);
	Vector2D operator - (Vector2D other);			//All mathematical operator overloads
												//Vector2 operator * (Matrix2 other);
	Vector2D operator * (float m);
	Vector2D operator / (float d);
};