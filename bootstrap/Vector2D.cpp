#include "Vector2D.h"
Vector2D::Vector2D()
{
	m_x = 0;
	m_y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	m_x = x;
	m_y = y;
}

float Vector2D::dot(Vector2D other)
{
	return m_x * other.m_x + m_y * other.m_y;
}

float Vector2D::magnitude()
{
	return sqrt((m_x*m_x) + (m_y*m_y));
}

void Vector2D::normalise()
{
	m_x = m_x / Vector2D::magnitude();
	m_y = m_y / Vector2D::magnitude();
}

//void Vector2::print()
//{
//	std::cout << m_x << ", " << m_y << std::endl;
//}

Vector2D Vector2D::operator + (Vector2D other)
{
	return Vector2D(m_x + other.m_x, m_y + other.m_y);
}

Vector2D Vector2D::operator - (Vector2D other)
{
	return Vector2D(m_x - other.m_x, m_y - other.m_y);
}

//Vector2 Vector2::operator * (Matrix2 other)
//{
//	return Vector2(m_x * other.m_a.m_x + m_y * other.m_a.m_y,
//		m_x * other.m_b.m_x + m_y * other.m_b.m_y);
//}

Vector2D Vector2D::operator*(float m)
{
	return Vector2D(m_x * m, m_y * m);
}

Vector2D Vector2D::operator/(float d)
{
	return Vector2D(m_x / d, m_y / d);
}
