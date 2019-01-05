#pragma once
#include "Precision.h"
#include <iostream>

namespace Maths {
	/*
	*	Holds a vector in two dimensions
	*/

	struct MATHS_API Vector2
	{
	public:

		real x;
		real y;

	public:
		
		Vector2();										// default constructor	
		explicit Vector2(const real a);							// explicit constructor
		explicit Vector2(const real x, const real y);			// explicit constructor
		Vector2(const Vector2& v);						// copy constructor
		~Vector2();										// destructor

		Vector2&										// assignment operator
			operator= (const Vector2& rhs);

		Vector2&										// clear 
			Clear(void);

		Vector2											// negate
			operator- (void) const;

		Vector2&										// negate
			Negate(void);

		real											// magnitude
			Magnitude(void) const;

		real											// square of the length
			SquareMagnitude(void) const;

		Vector2											// multiplication by a real
			operator* (const real a) const;

		Vector2&										// compound multiplication by a real
			operator*= (const real a);

		Vector2											// division by a real
			operator/ (const real a) const;

		Vector2&										// compound division by a real
			operator/= (const real a);

		Vector2											// addition 
			operator+ (const Vector2& v) const;

		Vector2&										// compound addition
			operator+= (const Vector2& v);

		Vector2											// substraction
			operator- (const Vector2& v) const;

		Vector2&										// compound substraction
			operator-= (const Vector2& v);

		real											// dot product
			operator* (const Vector2& v) const;

		real											// dot product
			Dot(const Vector2& v) const;

		Vector2&										// convert vector to a unit vector
			Normalize(void);

		Vector2&										//add scaled vector
			AddScaledVector(const Vector2& v, real s);

		Vector2&										// component product
			ComponentProductUpdate(const Vector2& rhs);

		Vector2											// component product without update
			ComponentProduct(const Vector2& rhs) const;
	};

	// inlined member functions

	// --------------------------------------------- operator-
	// return negated vector
	
	inline Vector2
		Vector2::operator- (void) const
	{
		return Vector2(-x, -y);
	}


	// ---------------------------------------------  LengthSquared
	// the square of the length

	inline real 
		Vector2::SquareMagnitude(void) const
	{
		return(x * x + y * y);
	}


	// ---------------------------------------------  multiplication by a real

	inline Vector2 
		Vector2::operator*(const real a) const
	{
		return Vector2(x * a, y * a);
	}


	// ---------------------------------------------  devision by a real

	inline Vector2 
		Vector2::operator/(const real a) const
	{
		return Vector2(x / a, y / a);
	}


	// ---------------------------------------------  addition

	inline Vector2											
		Vector2::operator+ (const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}


	// ---------------------------------------------  substraction

	inline Vector2
		Vector2::operator-(const Vector2 & v) const
	{
		return Vector2(x - v.x, y - v.y);
	}


	// ---------------------------------------------  * operator
	//dot product

	inline real 
		Vector2::operator*(const Vector2 & v) const
	{
		return (x * v.x + y * v.y);
	}


	// ---------------------------------------------  dot product

	inline real 
		Vector2::Dot(const Vector2 & v) const
	{
		return (x * v.x + y * v.y);
	}


	// ---------------------------------------------  component product without update

	inline Vector2										
		Vector2::ComponentProduct(const Vector2& rhs) const
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}


	// inlined non-member function

	// --------------------------------------------- operator*
	// multiplication by a real on the left

	inline Vector2
		operator* (const real a, const Vector2& v)
	{
		return (Vector2(a * v.x, a * v.y));
	}



	// non-inlined non-member function

	// --------------------------------------------- normalize
	//normalize a non member Vector2 v and return the result without changing v

	Vector2
		Normalize(const Vector2& v);


	// --------------------------------------------- << operator
	// print to string

	std::ostream& operator<<(std::ostream& os, const Vector2& v);
}