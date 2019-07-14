#include "enpch.h"
#include "Rectangle.h"


namespace Engine {

	Rectangle::Rectangle(const glm::vec3& p0, const glm::vec3& a, const glm::vec3& b, glm::vec3 normal)
		:m_P0(p0),
		m_A(a),
		m_B(b),
		m_Normal(normal)
	{
		m_InvArea = 1.0f / (glm::length(a) * glm::length(b));
	}

	Rectangle::~Rectangle()
	{
	}

	glm::vec3 Rectangle::Sample()
	{
		glm::vec2 samplePoint = m_Sampler->sample_unit_square();
		return(m_P0 + samplePoint.x * m_A + samplePoint.y * m_B);
	}

	float Rectangle::Pdf(ShadeRec& sr)
	{
		return m_InvArea;
	}

	glm::vec3 Rectangle::GetNormal(const glm::vec3& p)
	{
		return m_Normal;
	}

	GeometricObject* Rectangle::clone(void) const
	{
		EN_CORE_ASSERT(false, "not implemented");
		return nullptr;
	}

	bool Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		double t = glm::dot((m_P0 - ray.o), m_Normal) / glm::dot(ray.d, m_Normal);

		if (t <= kEpsilon)
			return (false);

		glm::vec3 p = ray.o + (float)t * ray.d;
		glm::vec3 d = p - m_P0;

		double ddota = glm::dot(d,  m_A);

		if (ddota < 0.0 || ddota > pow(m_A.length(),2))
			return (false);

		double ddotb = glm::dot(d, m_B);

		if (ddotb < 0.0 || ddotb > pow(m_B.length(), 2))
			return (false);

		tmin = t;
		sr.normal = m_Normal;
		sr.local_hit_point = p;

		return (true);
	}



}
