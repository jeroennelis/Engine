#pragma once

#include "GeometricObject.h"

namespace Engine {

	class Instance : public GeometricObject
	{
	public:
		Instance();

		Instance(GeometricObject* obj);

		Instance(const Instance& instance);

		virtual Instance* clone() const override;

		virtual ~Instance();

		Instance& operator= (const Instance& rhs);

		void SetObject(GeometricObject* object);

		void SetTransform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);

		virtual bool
			hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

		virtual bool ShadowHit(const Ray& ray, float& tmin) const override;


	private:

		GeometricObject* m_Object;

		glm::mat4 m_InvMatrix;

		bool m_TransformTexture;
	};
}
