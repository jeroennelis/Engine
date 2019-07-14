#include "enpch.h"
#include "Grid.h"

namespace Engine {

	Grid::Grid()
	{
	
	}

	Grid::~Grid()
	{
		for (GeometricObject* obj : m_Cells)
		{
			/*if(obj)
				delete obj;
			obj = nullptr;*/
		}
	}

	BBox Grid::GetBoundingBox()
	{
		return m_BBox;
	}

	void Grid::SetupCells()
	{
		glm::vec3 p0 = MinCoordinates();
		glm::vec3 p1 = MaxCoordinates();

		m_BBox.X0 = p0.x;
		m_BBox.Y0 = p0.y;
		m_BBox.Z0 = p0.z;
		m_BBox.X1 = p1.x;
		m_BBox.Y1 = p1.y;
		m_BBox.Z1 = p1.z;

		// compute the number of grid cells in the x, y, and z directions

		int num_objects = m_Objects.size();

		// dimensions of the grid in the x, y, and z directions

		double wx = p1.x - p0.x;
		double wy = p1.y - p0.y;
		double wz = p1.z - p0.z;

		double multiplier = 2.0;  	// multiplyer scales the number of grid cells relative to the number of objects

		double s = pow(wx * wy * wz / num_objects, 0.3333333);
		m_Nx = multiplier * wx / s + 1;
		m_Ny = multiplier * wy / s + 1;
		m_Nz = multiplier * wz / s + 1;

		// set up the array of grid cells with null pointers

		int num_cells = m_Nx * m_Ny * m_Nz;
		m_Cells.reserve(num_objects);

		for (int j = 0; j < num_cells; j++)
			m_Cells.push_back(NULL);

		// set up a temporary array to hold the number of objects stored in each cell

		std::vector<int> counts;
		counts.reserve(num_cells);

		for (int j = 0; j < num_cells; j++)
			counts.push_back(0);


		// put the objects into the cells

		BBox obj_bBox; 	// object's bounding box
		int index;  	// cell's array index

		
		for (int j = 0; j < num_objects; j++) {
			
			obj_bBox = m_Objects[j]->GetBoundingBox();
			
			// compute the cell indices at the corners of the bounding box of the object

			int ixmin = Clamp((obj_bBox.X0 - p0.x) * m_Nx / (p1.x - p0.x), 0, m_Nx - 1);
			int iymin = Clamp((obj_bBox.Y0 - p0.y) * m_Ny / (p1.y - p0.y), 0, m_Ny - 1);
			int izmin = Clamp((obj_bBox.Z0 - p0.z) * m_Nz / (p1.z - p0.z), 0, m_Nz - 1);
			int ixmax = Clamp((obj_bBox.X1 - p0.x) * m_Nx / (p1.x - p0.x), 0, m_Nx - 1);
			int iymax = Clamp((obj_bBox.Y1 - p0.y) * m_Ny / (p1.y - p0.y), 0, m_Ny - 1);
			int izmax = Clamp((obj_bBox.Z1 - p0.z) * m_Nz / (p1.z - p0.z), 0, m_Nz - 1);

			// add the object to the cells

			for (int iz = izmin; iz <= izmax; iz++) 					// cells in z direction
				for (int iy = iymin; iy <= iymax; iy++)					// cells in y direction
					for (int ix = ixmin; ix <= ixmax; ix++) {			// cells in x direction
						index = ix + m_Nx* iy + m_Nx * m_Ny * iz;

						if (counts.at(index) == 0) {
							m_Cells.at(index) = m_Objects[j];
							counts.at(index) += 1;  						// now = 1
						}
						else {
							if (counts[index] == 1) {
								Compound* compound_ptr = new Compound;	// construct a compound object
								compound_ptr->AddObject(m_Cells[index]); // add object already in cell
								compound_ptr->AddObject(m_Objects[j]);  	// add the new object
								m_Cells.at(index) = compound_ptr;			// store compound in current cell
								counts.at(index) += 1;  					// now = 2
							}
							else {										// counts[index] > 1
								m_Cells.at(index)->AddObject(m_Objects[j]);	// just add current object
								counts.at(index) += 1;						// for statistics only
							}
						}
					}
		}  // end of for (int j = 0; j < num_objects; j++)


		// erase the Compound::vector that stores the object pointers, but don't delete the objects

		m_Objects.erase(m_Objects.begin(), m_Objects.end());


		// display some statistics on counts
		// this is useful for finding out how many cells have no objects, one object, etc
		// comment this out if you don't want to use it

		int num_zeroes = 0;
		int num_ones = 0;
		int num_twos = 0;
		int num_threes = 0;
		int num_greater = 0;

		for (int j = 0; j < num_cells; j++) {
			if (counts[j] == 0)
				num_zeroes += 1;
			if (counts[j] == 1)
				num_ones += 1;
			if (counts[j] == 2)
				num_twos += 1;
			if (counts[j] == 3)
				num_threes += 1;
			if (counts[j] > 3)
				num_greater += 1;
		}

		std::cout << "num_cells =" << num_cells << std::endl;
		std::cout << "numZeroes = " << num_zeroes << "  numOnes = " << num_ones << "  numTwos = " << num_twos << std::endl;
		std::cout << "numThrees = " << num_threes << "  numGreater = " << num_greater << std::endl;

		// erase the temporary counts vector

		counts.erase(counts.begin(), counts.end());
	}

	bool Grid::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
	{
		double ox = ray.o.x;
		double oy = ray.o.y;
		double oz = ray.o.z;
		double dx = ray.d.x;
		double dy = ray.d.y;
		double dz = ray.d.z;

		double x0 = m_BBox.X0;
		double y0 = m_BBox.Y0;
		double z0 = m_BBox.Z0;
		double x1 = m_BBox.X1;
		double y1 = m_BBox.Y1;
		double z1 = m_BBox.Z1;
	
		double tx_min, ty_min, tz_min;
		double tx_max, ty_max, tz_max; 
	
		// the following code includes modifications from Shirley and Morley (2003)
	
		double a = 1.0 / dx;
		if (a >= 0) {
			tx_min = (x0 - ox) * a;
			tx_max = (x1 - ox) * a;
		}
		else {
			tx_min = (x1 - ox) * a;
			tx_max = (x0 - ox) * a;
		}
	
		double b = 1.0 / dy;
		if (b >= 0) {
			ty_min = (y0 - oy) * b;
			ty_max = (y1 - oy) * b;
		}
		else {
			ty_min = (y1 - oy) * b;
			ty_max = (y0 - oy) * b;
		}
	
		double c = 1.0 / dz;
		if (c >= 0) {
			tz_min = (z0 - oz) * c;
			tz_max = (z1 - oz) * c;
		}
		else {
			tz_min = (z1 - oz) * c;
			tz_max = (z0 - oz) * c;
		}
	
		double t0, t1;
	
		if (tx_min > ty_min)
			t0 = tx_min;
		else
			t0 = ty_min;
		
		if (tz_min > t0)
			t0 = tz_min;
		
		if (tx_max < ty_max)
			t1 = tx_max;
		else
			t1 = ty_max;
		
		if (tz_max < t1)
			t1 = tz_max;
			
		if (t0 > t1)
			return(false);
	
			
		// initial cell coordinates
	
		int ix, iy, iz;
	
		if (m_BBox.Inside(ray.o)) {  			// does the ray start inside the grid?
			ix = Clamp((ox - x0) * m_Nx / (x1 - x0), 0, m_Nx - 1);
			iy = Clamp((oy - y0) * m_Ny / (y1 - y0), 0, m_Ny - 1);
			iz = Clamp((oz - z0) * m_Nz / (z1 - z0), 0, m_Nz - 1);
		}
		else {
			glm::vec3 p = ray.o + (float)t0 * ray.d;  // initial hit point with grid's bounding box
			ix = Clamp((p.x - x0) * m_Nx / (x1 - x0), 0, m_Nx - 1);
			iy = Clamp((p.y - y0) * m_Ny / (y1 - y0), 0, m_Ny - 1);
			iz = Clamp((p.z - z0) * m_Nz / (z1 - z0), 0, m_Nz - 1);
		}
	
		// ray parameter increments per cell in the x, y, and z directions
	
		double dtx = (tx_max - tx_min) / m_Nx;
		double dty = (ty_max - ty_min) / m_Ny;
		double dtz = (tz_max - tz_min) / m_Nz;
		
		double 	tx_next, ty_next, tz_next;
		int 	ix_step, iy_step, iz_step;
		int 	ix_stop, iy_stop, iz_stop;
	
		if (dx > 0) {
			tx_next = tx_min + (ix + 1) * dtx;
			ix_step = +1;
			ix_stop = m_Nx;
		}
		else {
			tx_next = tx_min + (m_Nx - ix) * dtx;
			ix_step = -1;
			ix_stop = -1;
		}
	
		if (dx == 0.0) {
			tx_next = kHugeValue;
			ix_step = -1;
			ix_stop = -1;
		}
	
	
		if (dy > 0) {
			ty_next = ty_min + (iy + 1) * dty;
			iy_step = +1;
			iy_stop = m_Ny;
		}
		else {
			ty_next = ty_min + (m_Ny - iy) * dty;
			iy_step = -1;
			iy_stop = -1;
		}
	
		if (dy == 0.0) {
			ty_next = kHugeValue;
			iy_step = -1;
			iy_stop = -1;
		}
		
		if (dz > 0) {
			tz_next = tz_min + (iz + 1) * dtz;
			iz_step = +1;
			iz_stop = m_Nz;
		}
		else {
			tz_next = tz_min + (m_Nz - iz) * dtz;
			iz_step = -1;
			iz_stop = -1;
		}
	
		if (dz == 0.0) {
			tz_next = kHugeValue;
			iz_step = -1;
			iz_stop = -1;
		}
	
		
		// traverse the grid
	
		while (true) {	
			GeometricObject* object_ptr = m_Cells[ix + m_Nx * iy + m_Nx * m_Ny * iz];
		
			if (tx_next < ty_next && tx_next < tz_next) {
				if (object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < tx_next) {
					m_Material = object_ptr->GetMaterial();
					return (true);
				}
			
				tx_next += dtx;
				ix += ix_step;
						
				if (ix == ix_stop)
					return (false);
			} 
			else { 	
				if (ty_next < tz_next) {
					if (object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < ty_next) {
						m_Material = object_ptr->GetMaterial();
						return (true);
					}
				
					ty_next += dty;
					iy += iy_step;
								
					if (iy == iy_stop)
						return (false);
		 		}
		 		else {		
					if (object_ptr && object_ptr->hit(ray, tmin, sr) && tmin < tz_next) {
						m_Material = object_ptr->GetMaterial();
						return (true);
					}
				
					tz_next += dtz;
					iz += iz_step;
								
					if (iz == iz_stop)
						return (false);
		 		}
			}
		}
	}

	bool Grid::ShadowHit(const Ray& ray, float& tmin) const
	{
		/*for (GeometricObject* obj : m_Cells)
		{
			if (obj != nullptr)
				if (obj->ShadowHit(ray, tmin))
					return true;
		}*/
			
		return false;

	}

	glm::vec3 Grid::MinCoordinates()
	{
		BBox 	object_box;
		glm::vec3 p0(kHugeValue);

		int num_objects = m_Objects.size();

		for (int j = 0; j < num_objects; j++) {
			object_box = m_Objects[j]->GetBoundingBox();

			if (object_box.X0 < p0.x)
				p0.x = object_box.X0;
			if (object_box.Y0 < p0.y)
				p0.y = object_box.Y0;
			if (object_box.Z0 < p0.z)
				p0.z = object_box.Z0;
		}

		p0.x -= kEpsilon; p0.y -= kEpsilon; p0.z -= kEpsilon;

		return (p0);
	}

	glm::vec3 Grid::MaxCoordinates()
	{
		BBox object_box;
		glm::vec3 p1(-kHugeValue);

		int num_objects = m_Objects.size();

		for (int j = 0; j < num_objects; j++) {
			object_box = m_Objects[j]->GetBoundingBox();

			if (object_box.X1 > p1.x)
				p1.x = object_box.X1;
			if (object_box.Y1 > p1.y)
				p1.y = object_box.Y1;
			if (object_box.Z1 > p1.z)
				p1.z = object_box.Z1;
		}

		p1.x += kEpsilon; p1.y += kEpsilon; p1.z += kEpsilon;

		return (p1);
	}

}