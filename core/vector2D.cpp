#include "vector2D.h"

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return { m_x + other.m_x,m_y + other.m_y };
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return { m_x - other.m_x,m_y - other.m_y };
}

Vector2D Vector2D::operator*(const double n) const
{
	return { m_x*n,m_y*n};
}

Vector2D Vector2D::operator/(const double n) const
{
	return { m_x / n,m_y / n };
}

void Vector2D::normalize()
{
	double l = length();
	m_x /=l;
	m_y /= l;
}

Vector2D& operator+=(Vector2D& first, const Vector2D& second)
{
	first.m_x += second.m_x;
	first.m_y += second.m_y;
	return first;
}

Vector2D& operator-=(Vector2D& first, const Vector2D& second)
{
	first.m_x -= second.m_x;
	first.m_y -= second.m_y;
	return first;
}

Vector2D& operator*=(Vector2D& first, const double n)
{
	first.m_x *= n;
	first.m_y *= n;
	return first;
}

Vector2D& operator/=(Vector2D& first, const double n)
{
	first.m_x /= n;
	first.m_y /= n;
	return first;
}