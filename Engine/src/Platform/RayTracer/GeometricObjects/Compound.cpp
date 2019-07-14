#include "enpch.h"
#include "Compound.h"

namespace Engine {

	// ----------------------------------------------------------------  default constructor
	Compound::Compound()
		:GeometricObject()
	{
	}

	// ----------------------------------------------------------------  Clone
	Compound* Compound::clone() const
	{
		return (new Compound(*this));
	}

	// ----------------------------------------------------------------  Destructor
	Compound::~Compound()
	{
		DeleteObjects();
	}

	// ---------------------------------------------------------------- Assignment Operator
	Compound& Compound::operator=(const Compound& rhs)
	{
		if (this == &rhs)
			return (*this);

		GeometricObject::operator= (rhs);

		CopyObjects(rhs.m_Objects);

		return (*this);
	}

	void Compound::SetMaterial(RTMaterial* material)
	{
		int numObjects = m_Objects.size();

		for (GeometricObject* object: m_Objects)
			object->SetMaterial(material);
	}

	void Compound::AddObject(GeometricObject* object)
	{
		m_Objects.push_back(object);
	}


	bool Compound::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		double		t;
		glm::vec3	normal;
		glm::vec3	local_hit_point;
		bool		hit = false;
		tmin = kHugeValue;
		int 		num_objects = m_Objects.size();

		for (int j = 0; j < num_objects; j++)
			if (m_Objects[j]->hit(ray, t, sr) && (t < tmin)) {
				hit = true;
				tmin = t;
				m_Material = m_Objects[j]->GetMaterial();	// lhs is GeometricObject::material_ptr
				normal = sr.normal;
				local_hit_point = sr.local_hit_point;
			}

		if (hit) {
			sr.t = tmin;
			sr.normal = normal;
			sr.local_hit_point = local_hit_point;
		}

		return (hit);
	}

	void Compound::DeleteObjects()
	{
		int num_objects = m_Objects.size();

		for (int j = 0; j < num_objects; j++) {
			if(m_Objects[j])
				delete m_Objects[j];
			m_Objects[j] = NULL;
		}

		m_Objects.erase(m_Objects.begin(), m_Objects.end());
	}

	void Compound::CopyObjects(const std::vector<GeometricObject*>& objects)
	{
		DeleteObjects();
		int num_objects = objects.size();

		for (int j = 0; j < num_objects; j++)
			m_Objects.push_back(objects[j]->clone());
	}
}


