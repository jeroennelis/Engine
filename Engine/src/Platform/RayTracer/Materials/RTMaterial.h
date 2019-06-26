#pragma once


namespace Engine {

	class ShadeRec;

	class RTMaterial {
	
	public:
		RTMaterial();
		~RTMaterial();
		
		virtual glm::vec3 Shade(ShadeRec& sr);

		virtual glm::vec3 ShadeAreaLight(ShadeRec& sr);

		virtual glm::vec3 ShadePath(ShadeRec& sr);



	};
}
