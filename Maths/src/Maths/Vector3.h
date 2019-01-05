#pragma once

#include "Precision.h"
#include "Vector2.h"

namespace Maths {
	/*
	*	Holds a vector in two dimensions
	*/

	struct MATHS_API Vector3
	{
	public:

		union { real x, r; };
		union { real y, g; };
		union {	real z, b; };

	public:

		Vector3();										// default constructor	
		explicit Vector3(const real a);					// explicit constructor
		explicit Vector3
			(const real x, const real y, const real z);	// explicit constructor
		explicit Vector3
			(const Vector2& v, const real a);			// explicit constructor
		Vector3(const Vector3& v);						// copy constructor
		~Vector3();										// destructor

		Vector3&										// assignment operator
			operator= (const Vector3& rhs);

		const static Vector3 GRAVITY;
		const static Vector3 HIGH_GRAVITY;
		const static Vector3 UP;
		const static Vector3 RIGHT;
		const static Vector3 OUT_OF_SCREEN;
		const static Vector3 X;
		const static Vector3 Y;
		const static Vector3 Z;

		Vector3&										// set all members to 0
			Clear(void);

		Vector3											// negate
			operator- (void) const;

		Vector3&
			Negate(void);

		real											// length
			Magnitude(void) const;

		real											// square of the length
			SquareMagnitude(void) const;

		Vector3											// multiplication by a real
			operator* (const real a) const;

		Vector3&										// compound multiplication by a real
			operator*= (const real a);

		Vector3											// division by a real
			operator/ (const real a) const;

		Vector3&										// compound division by a real
			operator/= (const real a);

		Vector3											// addition 
			operator+ (const Vector3& v) const;

		Vector3&										// compound addition
			operator+= (const Vector3& v);

		Vector3											// substraction
			operator- (const Vector3& v) const;

		Vector3&										// compound substraction
			operator-= (const Vector3& v);

		real											// dot product
			operator* (const Vector3& v) const;

		real											// dot product
			Dot(const Vector3& v) const;

		Vector3											// cross product
			operator^(const Vector3& rhs) const;

		Vector3											// cross product
			Cross(const Vector3& rhs) const;

		Vector3&										// convert vector to a unit vector
			Normalize(void);

		Vector3&										//add scaled vector
			AddScaledVector(const Vector3& v, real s);

		Vector3&										// component product
			ComponentProductUpdate(const Vector3& rhs);

		Vector3											// component product without update
			ComponentProduct(const Vector3& rhs) const;
	};

	// inlined member functions

	// --------------------------------------------- operator-
	// return negated vector

	inline Vector3
		Vector3::operator- (void) const
	{
		return Vector3(-x, -y, -z);
	}


	// ---------------------------------------------  LengthSquared
	// the square of the length

	inline real											// square of the length
		Vector3::SquareMagnitude(void) const
	{
		return (x * x + y * y + z * z);
	}


	// ---------------------------------------------  multiplication by a real

	inline Vector3
		Vector3::operator*(const real a) const
	{
		return Vector3(x*a, y*a, z*a);
	}


	// ---------------------------------------------  devision by a real

	inline Vector3 
		Vector3::operator/(const real a) const
	{
		return Vector3(x / a, y / a, z / a);
	}


	// ---------------------------------------------  addition

	inline Vector3											
		Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}


	// ---------------------------------------------  substraction

	inline Vector3
		Vector3::operator-(const Vector3 & v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}


	// ---------------------------------------------  * operator
	//dot product

	inline real											
		Vector3::operator* (const Vector3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}


	// ---------------------------------------------  dot product

	inline real 
		Vector3::Dot(const Vector3 & v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}


	// ---------------------------------------------  cross product

	inline Vector3 
		Vector3::operator^(const Vector3 & rhs) const
	{
		return Vector3(
			y * rhs.z - z * rhs.y,
			x * rhs.z - z * rhs.x,
			x * rhs.y - y * rhs.x
			);
	}


	// ---------------------------------------------  cross product

	inline Vector3 
		Vector3::Cross(const Vector3 & rhs) const
	{
		return Vector3(
			y * rhs.z - z * rhs.y,
			x * rhs.z - z * rhs.x,
			x * rhs.y - y * rhs.x
		);
	}


	// ---------------------------------------------  component product without update

	inline Vector3
		Vector3::ComponentProduct(const Vector3& rhs) const
	{
		return Vector3(x * rhs.x, y * rhs.y, z*rhs.z);
	}
	   

	// non-inlined non-member function

	// --------------------------------------------- normalize
	//normalize a non member Vector2 v and return the result without changing v

	MATHS_API Vector3
		Normalize(const Vector3& v);


	// --------------------------------------------- << operator
	// print to string

	MATHS_API std::ostream& 
		operator<<(std::ostream& os, const Vector3& v);
}