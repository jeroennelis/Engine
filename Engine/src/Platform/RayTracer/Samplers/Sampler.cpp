#include "enpch.h"

#include "Sampler.h"
#include "Engine/Maths.h"
#include <algorithm>
#include <random>

namespace Engine {
	Sampler::Sampler()
		:num_samples(1),
		num_sets(1),
		count(0),
		jump(0)
	{
		samples.reserve(num_samples * num_sets);
		setup_shuffled_indices();
	}

	Sampler::Sampler(const int numSamples)
		:num_samples(numSamples),
		num_sets(1),
		count(0),
		jump(0)
	{
		samples.reserve(num_samples * num_sets);
		setup_shuffled_indices();
	}

	Sampler::Sampler(const int numSamples, const int numSets)
		:num_samples(numSamples),
		num_sets(numSets),
		count(0),
		jump(0)
	{
		samples.reserve(num_samples * num_sets);
		setup_shuffled_indices();
	}

	Sampler::Sampler(const Sampler& s)
		:num_samples(s.num_samples),
		num_sets(s.num_sets),
		count(s.count),
		jump(s.jump),
		samples(s.samples),
		shuffled_indices(s.shuffled_indices)
	{
	}


	Sampler::~Sampler()
	{
	}

	void Sampler::setup_shuffled_indices(void)
	{
		shuffled_indices.reserve(num_samples * num_sets);
		std::vector<int> indices;

		for (int j = 0; j < num_samples; j++)
			indices.push_back(j);

		for (int p = 0; p < num_sets; p++)
		{
			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(indices.begin(), indices.end(), g);
			for (int j = 0; j < num_samples; j++)
				shuffled_indices.push_back(indices[j]);
		}
	}

	glm::vec2 Sampler::sample_unit_square(void)
	{
		if (count % num_samples == 0)
			jump = (rand_int() % num_sets) * num_samples;
		return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}
}


