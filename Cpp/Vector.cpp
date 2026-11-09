#include "../h/Vector.h"
#include <cmath>

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(double x, double y) : x(x), y(y)
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(this->x * other.x, this->y * other.y);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2 Vector2::operator*(const double k) const
{
	return Vector2(this->x * k, this->y * k);
}

Vector2& Vector2::operator*=(const double k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const
{
	return Vector2(this->x / other.x, this->y / other.y);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2 Vector2::operator/(const double k) const
{
	if (k == 0)
	{
		return zero;
	}
	return Vector2(this->x / k, this->y / k);
}

Vector2& Vector2::operator/=(const double k)
{
	if (k == 0)
	{
		return *this = zero;
	}
	this->x /= k;
	this->y /= k;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return (this->x == other.x && this->y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

double Vector2::Magnitude() const
{
	return sqrt((x * x) + (y * y));
}

double Vector2::SqMagnitude()const
{
	return (x * x) + (y * y);
}

Vector2 Vector2::Normalized() const
{
	double mag = Magnitude();
	if (mag > 1e-15)
	{
		return Vector2(x / mag, y / mag);
	}
	return Vector2(0, 0);
}

double Vector2Distance(const Vector2& a, const Vector2& b)
{
	return (a - b).Magnitude();
}


double Vector2DistanceSq(const Vector2& a, const Vector2& b)
{
	return (a - b).SqMagnitude();
}

double Dot(const Vector2& a, const Vector2& b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

double Cross(const Vector2& a, const Vector2& b)
{
	return ((a.x * b.y) - (a.y * b.x));
}

const Vector2 Vector2::zero(0.0, 0.0);
const Vector2 Vector2::one(1.0, 1.0);
const Vector2 Vector2::up(0.0, -1.0);
const Vector2 Vector2::down(0.0, 1.0);
const Vector2 Vector2::left(-1.0, 0.0);
const Vector2 Vector2::right(1.0, 0.0);

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3 Vector3::operator*(const double k) const
{
	return Vector3(this->x * k, this->y * k, this->z * k);
}

Vector3& Vector3::operator*=(const double k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& other) const
{
	return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3 Vector3::operator/(const double k) const
{
	if (k == 0)
	{
		return zero;
	}
	return Vector3(this->x / k, this->y / k, this->z / k);
}

Vector3& Vector3::operator/=(const double k)
{
	if (k == 0)
	{
		return *this = zero;
	}
	this->x /= k;
	this->y /= k;
	this->z /= k;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

double Vector3::Magnitude() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

double Vector3::SqMagnitude() const
{
	return (x * x) + (y * y) + (z * z);
}

Vector3 Vector3::Normalized() const
{
	double mag = Magnitude();
	if (mag > 1e-15)
	{
		return Vector3(x / mag, y / mag, z / mag);
	}
	else
	{
		return Vector3(0, 0, 0);
	}
}

double Vector3Distance(const Vector3& a, const Vector3& b)
{
	return (a - b).Magnitude();
}


double Vector3DistanceSq(const Vector3& a, const Vector3& b)
{
	return (a - b).SqMagnitude();
}

double Dot(const Vector3& a, const Vector3& b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(((a.y * b.z) - (a.z * b.y)), ((a.z * b.x) - (a.x * b.z)), ((a.x * b.y) - (a.y * b.x)));
}

const Vector3 Vector3::zero(0.0, 0.0,0.0);
const Vector3 Vector3::one(1.0, 1.0, 1.0);
const Vector3 Vector3::up(0.0, 1.0, 0.0);
const Vector3 Vector3::down(0.0, -1.0, 0.0);
const Vector3 Vector3::left(-1.0, 0.0,0.0);
const Vector3 Vector3::right(1.0, 0.0, 0.0);
const Vector3 Vector3::forward(0.0, 0.0, 1.0);
const Vector3 Vector3::back(0.0, 0.0, -1.0);