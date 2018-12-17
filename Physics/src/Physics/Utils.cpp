#include "Utils.h"

namespace physics
{
	Vector3::Vector3()
		: X(0), Y(0), Z(0)
	{
	}

	Vector3::Vector3(const real x, const real y, const real z)
		: X(x), Y(y), Z(z)
	{
	}

	void Vector3::Invert()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}

	void Vector3::Clear()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	real Vector3::Magnitude() const
	{
		return real_sqrt(X * X + Y * Y + Z * Z);
	}

	real Vector3::SquareMagnitude() const
	{
		return X * X + Y * Y + Z * Z;
	}

	void Vector3::Normalize()
	{
		real l = Magnitude();
		if (l > 0)
		{
			(*this) *= ((real)1) / l;
		}
	}

	void Vector3::operator*=(const real value)
	{
		X *= value;
		Y *= value;
		Z *= value;
	}

	Vector3 Vector3::operator*(const real value) const
	{
		return Vector3(X * value, Y * value, Z * value);
	}

	void Vector3::operator+=(const Vector3 & v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;
	}

	Vector3 Vector3::operator+(const Vector3 & v) const
	{
		return Vector3(X + v.X, Y + v.Y, Z + v.Z);
	}

	void Vector3::operator-=(const Vector3 & v)
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
	}

	Vector3 Vector3::operator-(const Vector3 & v) const
	{
		return Vector3(X - v.X, Y - v.Y, Z - v.Z);
	}

	void Vector3::AddScaledVector(const Vector3 & vector, real scale)
	{
		X += vector.X * scale;
		Y += vector.Y * scale;
		Z += vector.Z * scale;
	}

	Vector3 Vector3::ComponentProduct(const Vector3 & vector) const
	{
		return { X * vector.X, Y * vector.Y, Z*vector.Z };
	}

	void Vector3::ComponentProductUpdate(const Vector3 & vector)
	{
		X *= vector.X;
		Y *= vector.Y;
		Z *= vector.Z;
	}

	real Vector3::ScalarProduct(const Vector3 & vector) const
	{
		return X * vector.X + Y * vector.Y + Z * vector.Z;
	}

	real Vector3::operator*(const Vector3 & vector) const
	{
		return X * vector.X + Y * vector.Y + Z * vector.Z;
	}

	Vector3 Vector3::vectorProduct(const Vector3 & vector) const
	{
		return{ Y * vector.Z - Z * vector.Y,
				Z * vector.X - X * vector.Z,
				X * vector.Y - Y * vector.X };
	}

	Vector3 Vector3::operator%(const Vector3 & vector) const
	{
		return{ Y * vector.Z - Z * vector.Y,
			Z * vector.X - X * vector.Z,
			X * vector.Y - Y * vector.X };
	}

	void Vector3::operator%=(const Vector3 & vector)
	{
		*this = vectorProduct(vector);
	}

	void Vector3::MakeOrthogonalBasis(Vector3 & a, Vector3 & b, Vector3 & c)
	{
		a.Normalize();
		c = a % b;
		if (c.SquareMagnitude() == 0) //TODO error can not create orthogonal basis
			return;
		c.Normalize();
		b = c % a;
	}


}

