#include "Vector3.h"

namespace Maths {

	const Vector3 Vector3::GRAVITY = Vector3(0, -9.81f, 0);
	const Vector3 Vector3::HIGH_GRAVITY = Vector3(0, -19.62f, 0);
	const Vector3 Vector3::UP = Vector3(0, 1, 0);
	const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
	const Vector3 Vector3::OUT_OF_SCREEN = Vector3(0, 0, 1);
	const Vector3 Vector3::X = Vector3(0, 1, 0);
	const Vector3 Vector3::Y = Vector3(1, 0, 0);
	const Vector3 Vector3::Z = Vector3(0, 0, 1);


	// --------------------------------------------- default constructor

	Vector3::Vector3()
		:x(0),
		y(0),
		z(0)
	{
	}


	// --------------------------------------------- explicit constructor

	Vector3::Vector3(const real a)
		:x(a),
		y(a),
		z(a)
	{
	}


	// --------------------------------------------- explicit constructor

	Vector3::Vector3(const real x, const real y, const real z)
		:x(x),
		y(y),
		z(z)
	{
	}


	// --------------------------------------------- explicit constructor

	Vector3::Vector3(const Vector2 & v, const real a)
		:x(v.x),
		y(v.y),
		z(a)
	{
	}


	// --------------------------------------------- copy constructor

	Vector3::Vector3(const Vector3 & v)
		:x(v.x),
		y(v.y),
		z(v.z)
	{
	}


	// --------------------------------------------- destructor

	Vector3::~Vector3()
	{
	}


	// --------------------------------------------- assignment operator

	Vector3&
		Vector3::operator=(const Vector3 & rhs)
	{
		if (this == &rhs)
			return (*this);

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return (*this);
	}


	// --------------------------------------------- clear
	// set all members to 0

	Vector3&
		Vector3::Clear(void)
	{
		x = 0;
		y = 0;
		z = 0;
		return (*this);
	}


	// --------------------------------------------- negate

	Vector3&
		Vector3::Negate(void)
	{
		x = -x;
		y = -y;
		z = -z;
		return (*this);
	}


	// ---------------------------------------------  length
	// length of the vector

	real 
		Vector3::Magnitude(void) const
	{
		return(real_sqrt(x * x + y * y + z * z));
	}


	// ---------------------------------------------  compound multiplication by a real

	Vector3&
		Vector3::operator*=(const real a)
	{
		x *= a;
		y *= a;
		z *= a;
		return (*this);
	}


	// ---------------------------------------------  compound division by a real

	Vector3&
		Vector3::operator/=(const real a)
	{
		x /= a;
		y /= a;
		z /= a;
		return (*this);
	}


	// ---------------------------------------------  compound addition

	Vector3&
		Vector3::operator+=(const Vector3 & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}
	

	// -------------------------------------------- - compound substraction

	Vector3&
		Vector3::operator-=(const Vector3 & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}


	// ---------------------------------------------  normalize
	// normalize this vector and return

	Vector3&
		Vector3::Normalize(void)
	{
		real length = Magnitude();
		x /= length;
		y /= length;
		z /= length;
		return (*this);
	}


	// ---------------------------------------------  add scaled vector

	Vector3&
		Vector3::AddScaledVector(const Vector3 & v, real s)
	{
		x += v.x * s;
		y += v.y * s;
		z += v.z * s;
		return(*this);
	}


	// ---------------------------------------------  component product

	Vector3&
		Vector3::ComponentProductUpdate(const Vector3 & rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return (*this);
	};


	// ---------------------------------------------  normalize
	// normalize vector v and return it

	Vector3 Normalize(const Vector3 & v)
	{
		real length = v.Magnitude();
		Vector3 n;
		n.x = v.x / length;
		n.y = v.y / length;
		n.z = v.z / length;
		return n;
	}

	MATHS_API std::ostream & operator<<(std::ostream & os, const Vector3 & v)
	{
		os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

}