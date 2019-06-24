#include "enpch.h"

#include "Jittered.h"
#include "Engine/Maths.h"

namespace Engine {

	Jittered::Jittered()
		:Sampler()
	{
		generate_samples();
	}

	Jittered::Jittered(const int numSamples)
		: Sampler(numSamples)
	{
		generate_samples();
	}

	Jittered::Jittered(const int numSamples, const int numSets)
		: Sampler(numSamples, numSets)
	{
		generate_samples();
	}

	Jittered::Jittered(const Jittered& j)
		: Sampler(j)
	{
	}


	Jittered::~Jittered()
	{
	}

	void Jittered::generate_samples(void)
	{
		int n = (int)sqrt(num_samples);

		for (int p = 0; p < num_sets; p++)
		{
			for (int j = 0; j < n; j++)
			{
				for (int k = 0; k < n; k++)
				{
					glm::vec2 sp((k + rand_float()) / n, (j + rand_float()) / n);
					samples.push_back(sp);
				}
			}
		}
	}
}


