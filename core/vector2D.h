#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

class Vector2D
{
public:
	//Inital Vector 2D object
	//Parameter:
	//x,y: position of vector;
	Vector2D(double x, double y) : m_x {x},m_y{y}{}
	Vector2D() {};
	~Vector2D() = default;
	
	double length() const { return sqrt(m_x * m_x + m_y * m_y); }
	
	Vector2D operator+ (const Vector2D& other) const;
	friend Vector2D& operator+=(Vector2D& first, const Vector2D& second);
	
	Vector2D operator- (const Vector2D& other) const;
	friend Vector2D& operator-=(Vector2D& first, const Vector2D& second) ;
	
	Vector2D operator* (const double n) const;
	friend Vector2D& operator*=(Vector2D& first, const double n) ;
	
	Vector2D operator/ (const double n) const;
	friend Vector2D& operator/=(Vector2D& first, const double n) ;

	void normalize();

	double get_x() const { return m_x; }
	double get_y() const { return m_y; }
	void set_x(double x) { m_x = x; }
	void set_y(double y) { m_y = y; }
private:
	double m_x{};
	double m_y{};
};


#endif // VECTOR2D_H
