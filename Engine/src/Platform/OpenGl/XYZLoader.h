#pragma once

namespace Engine {

	struct RawModel;

	class XYZLoader
	{
	public:
		XYZLoader();
		~XYZLoader();

		static std::vector<RawModel> LoadXYZModel(const std::string& filePath);

	private:
		static std::vector<std::string> SplitString(const std::string& s, char delim);
		static RawModel ConvertToRawModel(const std::vector<float>& verticesVector, const std::vector<float>& colorsVector);
		static RawModel ConvertToRawModel(const std::vector<float>& data);

	};
}