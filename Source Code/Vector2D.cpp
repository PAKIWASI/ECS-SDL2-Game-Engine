#include "Vector2D.h"

Vector2D::Vector2D()
{
	this->Zero();
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}


Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;          // this : Vector2D*  (pointer to Vector 2D)
	this->y += vec.y;          // *this : Vector2D  (dereferenced pointer :basic obj)

	return *this;               // return type is ref to Vector2D (Vector2D&) so we return the obj (Vector2D& = *this(Vector2D obj))
}

Vector2D& Vector2D::sub(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::xply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divd(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}


Vector2D& Vector2D::operator+=(const Vector2D& vec)
{                                                             //LHS    //RHS
	return this->add(vec);       // LHS += RHS ->   *(Vector2D*).add(vec)
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->sub(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->xply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divd(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= static_cast<float>(i);
	this->y *= static_cast<float>(i);
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;  
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.sub(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.xply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.divd(v2);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	return stream << '(' << vec.x << ',' << vec.y << ')';
}
