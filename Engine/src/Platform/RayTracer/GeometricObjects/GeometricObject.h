#pragma once

// this file contains the declaration of the class GeometricObject

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

#include "../Utilities/Constants.h"

namespace Engine {
	class GeometricObject {

	public:

		GeometricObject(void);									// default constructor

		GeometricObject(const GeometricObject& object);			// copy constructor

		virtual GeometricObject*								// virtual copy constructor
			clone(void) const = 0;

		virtual 												// destructor
			~GeometricObject(void);

		virtual bool
			hit(const Ray& ray, double& t, ShadeRec& s) const = 0;


		// the following three functions are only required for Chapter 3

		void
			set_color(const glm::vec3& c);

		void
			set_color(const float r, const float g, const float b);

		glm::vec3
			get_color(void);


	protected:

		glm::vec3   color;						// only used for Bare Bones ray tracing

		GeometricObject&						// assignment operator
			operator= (const GeometricObject& rhs);
	};


	// --------------------------------------------------------------------  set_colour

	inline void
		GeometricObject::set_color(const glm::vec3& c) {
		color = c;
	}

	// --------------------------------------------------------------------  set_colour

	inline void
		GeometricObject::set_color(const float r, const float g, const float b) {
		color.r = r;
		color.b = b;
		color.g = g;
	}

	// --------------------------------------------------------------------  get_colour

	inline glm::vec3
		GeometricObject::get_color(void) {
		return (color);
	}
}
					


