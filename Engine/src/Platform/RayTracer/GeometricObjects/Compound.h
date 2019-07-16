#pragma once

#include "GeometricObject.h"

namespace Engine {

	class Compound : public GeometricObject
	{
	public:

		// Default Constructor
		Compound();

		// Clone
		virtual Compound* clone() const override;

		// Destructor
		virtual ~Compound();

		// Assignment Operator
		Compound& operator= (const Compound& c);

		// Set Material
		virtual void SetMaterial(Material* material_ptr);

		// Add Object
		virtual void AddObject(GeometricObject* object_ptr) override;

		// Hit
		virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const override;

		virtual bool ShadowHit(const Ray&, float& tmin) const override { return false; };

	protected:
			std::vector<GeometricObject*> m_Objects;

	private:
		// Delete all objects
		void DeleteObjects();

		// Copy Objects
		void CopyObjects(const std::vector<GeometricObject*>& objects);

	};
}
