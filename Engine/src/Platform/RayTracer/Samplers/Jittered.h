#pragma once
#include "Sampler.h"

namespace Engine {

	class Jittered :
		public Sampler
	{
	public:
		Jittered();
		Jittered(const int numSamples);
		Jittered(const int numSamples, const int numSets);
		Jittered(const Jittered& j);
		~Jittered();

	private:
		virtual void generate_samples(void);
	};
}



