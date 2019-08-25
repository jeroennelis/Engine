#include "enpch.h"
#include "RTReflective.h"

namespace Engine {

	RTReflective::RTReflective()
		:RTPhong(),
		m_ReflectiveBRDF(new RTPerfectSpecular)
	{
	}

	RTReflective::RTReflective(const RTReflective& rm)
		: RTPhong(rm) 
	{

		/*if (rm.m_ReflectiveBRDF)
			m_ReflectiveBRDF = rm.m_ReflectiveBRDF->clone();
		else
			m_ReflectiveBRDF = NULL;*/
	}

	RTReflective& RTReflective::operator=(const RTReflective& rhs)
	{
		/*if (this == &rhs)
			return (*this);

		RTPhong::operator=(rhs);

		if (m_ReflectiveBRDF) {
			delete m_ReflectiveBRDF;
			m_ReflectiveBRDF = NULL;
		}

		if (rhs.m_ReflectiveBRDF)
			m_ReflectiveBRDF = rhs.m_ReflectiveBRDF->clone();*/

		return (*this);
	}

	RTReflective* RTReflective::clone() const
	{
		return (new RTReflective(*this));
	}

	RTReflective::~RTReflective()
	{
	}

	void RTReflective::SetKr(const float kr)
	{
		m_ReflectiveBRDF->SetKr(kr);
	}

	void RTReflective::SetCr(Texture_temp* cr)
	{
		m_ReflectiveBRDF->SetCr(cr);
	}

	glm::vec3 RTReflective::Shade(ShadeRec& sr)
	{
		glm::vec3 L(RTPhong::Shade(sr));

		glm::vec3 wo = -sr.ray.d;
		glm::vec3 wi;
		glm::vec3 fr = m_ReflectiveBRDF->SampleF(sr, wo, wi);
		Ray reflectedRay(sr.local_hit_point, wi);

		L += fr * sr.w->tracer_ptr->trace_ray(reflectedRay, sr.depth + 1) * glm::dot(sr.normal, wi);

		return L;
	}

}


