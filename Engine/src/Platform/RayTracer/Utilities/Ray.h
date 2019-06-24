#pragma once

namespace Engine {


	class Ray {
	public:

		glm::vec3		o;  	// origin 
		glm::vec3		d; 		// direction 

		Ray(void);

		Ray(const glm::vec3& origin, const glm::vec3& dir);

		Ray(const Ray& ray);

		Ray&
			operator= (const Ray& rhs);

		~Ray(void);
	};
}
