#pragma once

namespace Engine {

	class Mesh
	{
	public:
		std::vector<glm::vec3> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<glm::vec3> Normals;
		std::vector<std::vector<int>> VertexFaces;
		std::vector<float> U;
		std::vector<float> V;
		int NumVertices;
		int NumTriangles;

		Mesh();

		Mesh(const Mesh& mesh);

		~Mesh();

		Mesh& operator=(const Mesh& rhs);
	};
}