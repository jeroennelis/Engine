#include "enpch.h"
#include "Engine/Maths.h"

#include "NRooks.h"

namespace Engine {
	NRooks::NRooks()
		:Sampler()
	{
		generate_samples();
	}

	NRooks::NRooks(const int numSamples)
		: Sampler(numSamples)
	{
		generate_samples();
	}

	NRooks::NRooks(const int numSamples, int numSets)
		: Sampler(numSamples, numSets)
	{
		generate_samples();
	}

	NRooks::NRooks(const NRooks& nr)
		: Sampler(nr)
	{
		generate_samples();
	}


	NRooks::~NRooks()
	{
	}

	void NRooks::generate_samples(void)
	{
		// first generate samples along the main diagonal

		for (int p = 0; p < num_sets; p++)
		{
			for (int j = 0; j < num_samples; j++)
			{
				glm::vec2 pv;
				pv.x = (j + rand_float()) / num_samples;
				pv.y = (j + rand_float()) / num_samples;
				samples.push_back(pv);
			}
			//shuffle the samples, so they are no longer on the diagonal

			shuffle_x_coordinates();
			shuffle_y_coordinates();
		}
	}

	void NRooks::shuffle_x_coordinates()
	{
		for (int p = 0; p < num_sets; p++)
		{
			for (int i = 0; i < num_samples - 1; i++)
			{
				int target = rand_int() % num_samples + p * num_samples;
				float temp = samples[i + p * num_samples + 1].x;
				samples[i + p * num_samples + 1].x = samples[target].x;
				samples[target].x = temp;
			}
		}
	}

	void NRooks::shuffle_y_coordinates()
	{
		for (int p = 0; p < num_sets; p++)
		{
			for (int i = 0; i < num_samples - 1; i++)
			{
				int target = rand_int() % num_samples + p * num_samples;
				float temp = samples[i + p * num_samples + 1].y;
				samples[i + p * num_samples + 1].y = samples[target].y;
				samples[target].y = temp;
			}
		}
	}
}


