#pragma once

#include <math.h>
#include "Vector2D.h"

class PhysObject
{
public:
	virtual void Debug() = 0;
	virtual void updatePos() = 0;
	float x, y;
	Vector2D velocity;
	Vector2D position;
	float mass;
};

class Rect : public PhysObject
{
public:
	Rect(float x, float y, float w, float h);
	void Debug() {};
	void updatePos();
	float width;
	float height;
	float r;
};

class Line : public PhysObject
{
public:
	Line();
	Line(float x1, float y1, float x2, float y2);
	void updatePos();
	void Debug() {};
	float xo, yo;
	bool active = false;
};

class Circ : public PhysObject
{
public:
	Circ(float xin, float yin, float rin);
	void Debug() {};
	void updatePos();
	float r;
};

class PhysManager
{
public:
	void applyForce(Circ &b, Vector2D force);
	void updateCollision(Line &a, Circ &b);
	void updateGravity(Circ &b);
	void Reflect(Line &a, Circ &b, float intensity);
};