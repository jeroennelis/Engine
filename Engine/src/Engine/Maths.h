#pragma once
#include "openvr.h"

namespace Engine {

	class Maths
	{
	public:
		inline static glm::mat4 GLMMat4(const vr::HmdMatrix44_t& mat){
			return glm::mat4(
				mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
				mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
				mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
				mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
			);
		}

		inline static glm::mat4 GLMMat4(const vr::HmdMatrix34_t& mat) {
			return glm::mat4 (
				mat.m[0][0], mat.m[1][0], mat.m[2][0], 0.0,
				mat.m[0][1], mat.m[1][1], mat.m[2][1], 0.0,
				mat.m[0][2], mat.m[1][2], mat.m[2][2], 0.0,
				mat.m[0][3], mat.m[1][3], mat.m[2][3], 1.0f
			);
		}
	};
}
