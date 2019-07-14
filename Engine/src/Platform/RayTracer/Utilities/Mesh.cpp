#include "enpch.h"

#include "Mesh.h"

namespace Engine {

	Mesh::Mesh()
		:NumVertices(0),
		NumTriangles(0)
	{
	}

	Mesh::Mesh(const Mesh& mesh)
		: Vertices(mesh.Vertices),
		Indices(mesh.Indices),
		Normals(mesh.Normals),
		U(mesh.U),
		V(mesh.V),
		NumVertices(mesh.NumVertices),
		NumTriangles(mesh.NumTriangles)
	{
	}
	Mesh::~Mesh()
	{
		EN_CORE_ERROR("test");
	}

	Mesh& Mesh::operator=(const Mesh& rhs)
	{
		if (this == &rhs)
			return (*this);

		Vertices = rhs.Vertices;
		Normals = rhs.Normals;
		U = rhs.U;
		V = rhs.V;
		NumVertices = rhs.NumVertices;
		NumTriangles = rhs.NumTriangles;

		return (*this);
	}
}