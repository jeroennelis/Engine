#include "Vector2.h"

namespace Maths {

	// --------------------------------------------- default constructor

	Vector2::Vector2()
		:x(0),
		y(0)
	{
	}


	// --------------------------------------------- explicit constructor

	Vector2::Vector2(const real a)
		:x(a),
		y(a)
	{
	}


	// --------------------------------------------- explicit constructor

	Vector2::Vector2(const real x, const real y)
		:x(x),
		y(y)
	{
	}


	// --------------------------------------------- copy constructor

	Vector2::Vector2(const Vector2 & v)
		: x(v.x),
		y(v.y)
	{
	}


	// --------------------------------------------- destructor

	Vector2::~Vector2()
	{
	}


	// --------------------------------------------- assignment operator

	Vector2&
		Vector2::operator=(const Vector2 & rhs)
	{
		if (this == &rhs)
			return (*this);

		x = rhs.x;
		y = rhs.y;

		return (*this);
	}


	// --------------------------------------------- clear

	Vector2& 
		Vector2::Clear(void)
	{
		x = 0;
		y = 0;
		return (*this);
	}


	// --------------------------------------------- negate

	Vector2&
		Vector2::Negate(void)
	{
		x = -x;
		y = -y;
		return (*this);
	}


	// ---------------------------------------------  length
	// length of the vector

	real
		Vector2::Magnitude() const
	{ 
		return (real_sqrt(x * x + y * y));
	}


	// ---------------------------------------------  compound multiplication by a real

	Vector2&
		Vector2::operator*=(const real a)
	{
		x *= a;
		y *= a;
		return (*this);
	}

	// ---------------------------------------------  compound division by a real

	Vector2&
		Vector2::operator/= (const real a)
	{
		x /= a;
		y /= a;
		return (*this);
	}


	// ---------------------------------------------  compound addition

	Vector2&
		Vector2::operator+=(const Vector2 & v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}


	// ---------------------------------------------  compound substraction

	Vector2&
		Vector2::operator-=(const Vector2 & v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	// ---------------------------------------------  normalize
	// normalize this vector and return

	Vector2&
		Vector2::Normalize(void)
	{
		real length = Magnitude();
		x /= length;
		y /= length;
		return (*this);
	}


	// ---------------------------------------------  add scaled vector
	
	Vector2&
		Vector2::AddScaledVector(const Vector2 & v, real s)
	{
		x += v.x * s;
		y += v.y * s;
		return(*this);
	}


	// ---------------------------------------------  component product

	Vector2&
		Vector2::ComponentProductUpdate(const Vector2 & rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return (*this);
	}


	// ---------------------------------------------  normalize
	// normalize vector v and return it

	Vector2
		Normalize(const Vector2 & v)
	{
		real length = v.Magnitude();
		Vector2 n;
		n.x = v.x / length;
		n.y = v.y / length;
		return n;
	}


	// ---------------------------------------------  operator <<
	// convert vector2 into string

	std::ostream & operator<<(std::ostream & os, const Vector2 & v)
	{
		os << "Vector2(" << v.x << " ," << v.y << ")";
		return os;
	}
}