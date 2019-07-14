// this file contains the definition of the class GeometricObject 

#include "enpch.h"
#include "GeometricObject.h"

namespace Engine{

	// ---------------------------------------------------------------------- default constructor

	GeometricObject::GeometricObject(void)
	{}


	// ---------------------------------------------------------------------- copy constructor

	GeometricObject::GeometricObject(const GeometricObject& object)
	{}


	// ---------------------------------------------------------------------- assignment operator

	GeometricObject&
		GeometricObject::operator= (const GeometricObject& rhs) {

		if (this == &rhs)
			return (*this);

		return (*this);
	}


	// ---------------------------------------------------------------------- destructor

	GeometricObject::~GeometricObject(void) {}
	bool GeometricObject::ShadowHit(const Ray &, float& tmin) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return false;
	}

	void GeometricObject::AddObject(GeometricObject* object) {}

	inline glm::vec3 GeometricObject::Sample()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	inline float GeometricObject::Pdf(ShadeRec& sr)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return 1.0f;
	}

	glm::vec3 GeometricObject::GetNormal(const glm::vec3& p)
	{
		EN_CORE_ASSERT(false, "not implemented");
		return glm::vec3();
	}

	BBox GeometricObject::GetBoundingBox()
	{
		EN_CORE_ASSERT(false, "not implemented");
		return BBox();
	}
}


