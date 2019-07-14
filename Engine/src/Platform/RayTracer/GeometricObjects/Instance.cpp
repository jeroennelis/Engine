#include "enpch.h"
#include "Instance.h"

namespace Engine {
	
	Engine::Instance::Instance()
		:GeometricObject(),
		m_Object(nullptr),
		m_InvMatrix(1.0),
		m_TransformTexture(true)
	{
	}

	Instance::Instance(GeometricObject* obj)
		:GeometricObject(),
		m_Object(obj),
		m_InvMatrix(1.0),
		m_TransformTexture(true)
	{
	}

	Instance::Instance(const Instance& instance)
		: GeometricObject(instance),
		m_InvMatrix(instance.m_InvMatrix),
		m_TransformTexture(instance.m_TransformTexture)
	{
		if (instance.m_Object)
			m_Object = instance.m_Object->clone();
		else  m_Object = NULL;
	}

	Instance* Instance::clone() const
	{
		return (new Instance(*this));
	}

	Instance::~Instance()
	{
		if (m_Object) {
			delete m_Object;
			m_Object = NULL;
		}
	}

	Instance& Instance::operator=(const Instance& rhs)
	{
		if (this == &rhs)
			return (*this);

		GeometricObject::operator=(rhs);

		if (m_Object) {
			delete m_Object;
			m_Object = NULL;
		}

		if (rhs.m_Object)
			m_Object = rhs.m_Object->clone();
		else
			m_Object = NULL;

		m_InvMatrix = rhs.m_InvMatrix;
		m_TransformTexture = rhs.m_TransformTexture;

		return (*this);
	}

	void Instance::SetObject(GeometricObject* object)
	{
		m_Object = object;
	}

	void Instance::SetTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	{
		glm::mat4 posMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z)));

		glm::mat4 rotXMatrix = (glm::rotate(glm::radians(rot.x), glm::vec3(1, 0, 0)));
		glm::mat4 rotYMatrix = (glm::rotate(glm::radians(rot.y), glm::vec3(0, 1, 0)));
		glm::mat4 rotZMatrix = (glm::rotate(glm::radians(rot.z), glm::vec3(0, 0, 1)));
		glm::mat4 rotMatrix = glm::inverse(rotXMatrix * rotYMatrix * rotZMatrix);

		

		glm::mat4 scaleMatrix = glm::inverse(glm::scale(glm::vec3(scale.x, scale.y, scale.z)));

		m_InvMatrix =  scaleMatrix * rotMatrix * posMatrix;
	}

	bool Instance::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		Ray inverseRay(ray);
		inverseRay.o = m_InvMatrix * glm::vec4(inverseRay.o, 1.0);
		inverseRay.d = glm::normalize(m_InvMatrix * glm::vec4(inverseRay.d, 0.0));

		if (m_Object->hit(inverseRay, tmin, sr))
		{
			sr.normal = glm::transpose(m_InvMatrix) * glm::vec4(sr.normal, 0.0);
			sr.normal = glm::normalize(sr.normal);

			if (m_Object->GetMaterial())
				m_Material = m_Object->GetMaterial();

			if (!m_TransformTexture)
				sr.local_hit_point = ray.o + (float)tmin * ray.d;
			
			return true;
		}

		return false;
	}

	bool Instance::ShadowHit(const Ray& ray, float& tmin) const
	{
		return m_Object->ShadowHit(ray, tmin);
	}
}