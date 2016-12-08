#include "Physics2D.h"
#include <math.h>
//line is boundary
//circ is the object
void PhysManager::updateCollision(Line &a, Circ &b)
{
	


	//3.14p = 180d
	//1p = 57.3d


	
	float lineDeltaX = a.xo - a.x;
	float lineDeltaY = a.yo - a.y;
	float LineLength = sqrt(lineDeltaX*lineDeltaX + lineDeltaY*lineDeltaY);
	float CollisionDistance = sqrt(LineLength*LineLength + b.r*b.r);
	float CurrentDistance = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) + sqrt((a.xo - b.x)*(a.xo - b.x) + (a.yo - b.y)*(a.yo - b.y));

	//collision detection
	if (CurrentDistance <= CollisionDistance + 3)
	{
		//collision resolution
		Vector2D dir = b.position;
		float mag = dir.magnitude();
		dir.normalise();
		float adj = -atan2(lineDeltaX, lineDeltaY);
		float hyp = dir.magnitude();
		float theta = acos(adj / hyp);
		Vector2D newdir = Vector2D(cos(theta), sin(theta));
		b.velocity = newdir *2.0f;
	//	float newVecY = -b.velocity.m_y * sin(lineDeltaX / lineDeltaY);
	//	float newVecX = -b.velocity.m_x * sin(lineDeltaY / lineDeltaX);
	//	//float newVecX = (atan2(lineDeltaX, lineDeltaY));
	//	b.velocity.m_y = newVecY;
	//	//b.vector.m_x = newVecX;
	}

	
}

void PhysManager::updateGravity(Circ &b)
{
	b.velocity.m_y = b.velocity.m_y - 0.2f;
}

Circ::Circ(float xin, float yin, float rin)
{
	
	x = xin;
	y = yin;
	r = rin;
	position = Vector2D(this->x, this->y);
}

void Circ::updatePos()
{
	x = x + velocity.m_x;
	y = y + velocity.m_y;
}

Line::Line(float x1, float y1, float x2, float y2)
{
	x = x1;
	y = y1;
	xo = x2;
	yo = y2;
}

void Line::updatePos()
{
	x += velocity.m_x;
	xo += velocity.m_x;
	y += velocity.m_y;
	yo += velocity.m_y;
}

void Rect::updatePos()
{

}
