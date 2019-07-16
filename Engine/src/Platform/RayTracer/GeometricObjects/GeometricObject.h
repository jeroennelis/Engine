#pragma once

// this file contains the declaration of the class GeometricObject

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

#include "../Utilities/Constants.h"

#include "..//Utilities/BBox.h"

#include "Engine/Materials/Material.h"

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

		virtual bool
			ShadowHit(const Ray&, float& tmin) const;




		inline Material* GetMaterial() { return m_Material; }
		inline void SetMaterial(Material* material) { m_Material = material; }

		virtual void AddObject(GeometricObject* object);		// used for compounds

		virtual glm::vec3 Sample();

		virtual float Pdf(ShadeRec& sr);

		virtual glm::vec3 GetNormal(const glm::vec3& p);

		virtual BBox GetBoundingBox();

	protected:

		mutable Material* m_Material;

		GeometricObject&						// assignment operator
			operator= (const GeometricObject& rhs);
	};	
}
					
 

