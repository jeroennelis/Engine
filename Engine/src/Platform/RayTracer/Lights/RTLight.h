#pragma once



namespace Engine {

	class ShadeRec;

	class RTLight
	{
	public:
		RTLight();
		~RTLight();

		virtual glm::vec3 GetDirection(ShadeRec& sr) = 0;

		virtual glm::vec3 L(ShadeRec& sr) = 0;


	private:
		bool shadows;

	};
}