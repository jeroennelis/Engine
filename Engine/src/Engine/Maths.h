#pragma once
#include <openvr.h>

namespace Engine {

	class Maths
	{
	public:
		static glm::mat4 GLMMat4(const vr::HmdMatrix44_t& mat);

		static glm::mat4 GLMMat4(const vr::HmdMatrix34_t& mat);
	};
}
