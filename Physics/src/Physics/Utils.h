#pragma once
#include <iostream>
#include <math.h>

#include "core.h"
#include "Precision.h"

namespace physics {

	/*
	* Holds a vector in three dimensions
	* four dimentions allocated for memory purposes
	*/
	struct PHYSICS_API Vector3
	{
		real X;
		real Y;
		real Z;

	private:
		real pad;

	public:
		/*
		* default constructor, creates zero vecor
		*/

		Vector3();

		/*
		*explicit constructor
		*/
		Vector3(const real x, const real y, const real z);
		
		/*
		* flips components of vector
		*/
		void Invert();		

		/**
		* clear the vector
		**/
		void Clear();		

		/*
		* gets magnitude of vector
		*/
		real Magnitude() const;

		/*
		* returns squared magnitude of this vector
		*/
		real SquareMagnitude() const;		

		/*
		* Normalize this vector
		*/
		void Normalize();

		/*
		* multiplies the vector with a scalar
		*/
		void operator*= (const real value);		

		/*
		*returns the result of the multiplication between this vector and a scalar value
		*
		*/
		Vector3 operator*(const real value) const;

		/*
		* adds another vector v to this vector
		*/
		void operator+= (const Vector3& v);

		/*
		* returns result of the addition of another vector v to this vector
		*/
		Vector3 operator+ (const Vector3 &v) const;

		/*
		* substracts another vector from this vector
		*/
		void operator-= (const Vector3 &v);		

		/*
		* returns result of the substraction of another vector v from this vector
		*/
		Vector3 operator-(const Vector3 &v)const;
		
		/*
		* adds another vector, scaled by a given amount, to this vector
		*/
		void AddScaledVector(const Vector3 &vector, real scale);

		/*
		* returns the result component-wise product of another vector and this vector
		*/
		Vector3 ComponentProduct(const Vector3 &vector) const;		

		/*
		* calculate the component-wise product of another vector and this vector
		* and update this vector
		*/
		void ComponentProductUpdate(const Vector3 &vector);		

		/*
		* returns the result of the scalar product of another vector with this vector
		*/
		real ScalarProduct(const Vector3 &vector)const;		

		/*
		* returns the result of the scalar product of another vector with this vector
		* using the * operator
		*/
		real operator*(const Vector3 &vector) const;		

		/*
		* returns the result of the vector product of another vector with this vector
		*/
		Vector3 vectorProduct(const Vector3 &vector) const;		

		/*
		* returns the result of the vector product of another vector with this vector
		* using the % operator
		*/
		Vector3 operator%(const Vector3 &vector) const;		

		/*
		* sets this vector to the result of the vector product of another vector with this vector
		* using the % operator
		*/
		void operator %=(const Vector3 &vector);		

		/*
		* construct orthogonal basis starting from two nonparallel vectors a and b.
		* the direction of a will not change at all, but a will be normalised.
		* c is entirely detirmined from a and b
		*/
		static void MakeOrthogonalBasis(Vector3 &a, Vector3 &b, Vector3 &c);		

		/*
		* convert vector to a string
		*/
		friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
		{
			os << "Vector3[" << v.X << ", " << v.Y << ", " << v.Z << "]";
			return os;
		}
	};
}