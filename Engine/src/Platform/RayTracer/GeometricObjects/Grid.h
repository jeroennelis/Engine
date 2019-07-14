#pragma once

#include "Compound.h"

#include "Engine/Maths.h"

namespace Engine {

	class Grid : public Compound
	{

	public:
		Grid();

		Grid(const Grid& grid);

		~Grid();

		virtual BBox GetBoundingBox() override;

		void SetupCells();

		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const override;

		virtual bool ShadowHit(const Ray& ray, float& tmin) const override;



	private:
		std::vector<GeometricObject*> m_Cells;
		BBox m_BBox;
		int m_Nx, m_Ny, m_Nz;

		glm::vec3 MinCoordinates();
		glm::vec3 MaxCoordinates();
	};
}