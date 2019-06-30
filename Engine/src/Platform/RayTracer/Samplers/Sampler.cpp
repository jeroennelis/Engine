#include "enpch.h"

#include "Sampler.h"
#include "Engine/Maths.h"
#include <algorithm>
#include <random>
#include "../Utilities/Constants.h"

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

	glm::vec2 Sampler::sample_unit_disk(void)
	{
		if (count % num_samples == 0)  									// start of a new pixel
			jump = (rand_int() % num_sets) * num_samples;

		return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}

	glm::vec3 Sampler::SampleHemisphere()
	{
		if (count % num_samples == 0)
			jump = (rand_int() % num_sets) * num_samples;
		return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
	}

	void Sampler::map_samples_to_unit_disk(void)
	{
		int size = samples.size();	
		float r, phi;					//porlar coordinates
		glm::vec2 sp;					//sample point on unit disk

		disk_samples.reserve(size);

		for (int j = 0; j < size; j++)
		{
			//map sample points to [-1,1] [-1,1] range
			sp.x = 2.0 * samples[j].x - 1.0;
			sp.y = 2.0 * samples[j].y - 1.0;

			if (sp.x > -sp.y)				//sector 1 or 2
			{
				if (sp.x > sp.y)			//sector 1
				{
					r = sp.x;
					phi = sp.y / sp.x;
				}
				else
				{
					r = sp.y;				//sector 2
					phi = 2 - sp.x / sp.y;
				}	
			}
			else
			{								//sector 3 or 4
				if (sp.x < sp.y)			//sector 3
				{
					r = -sp.x;
					phi = 4 + sp.y / sp.x;
				}
				else
				{							//secor 4
					r = -sp.y;
					if (sp.y != 0.0)			//avoid division by zero
						phi = 6 + sp.x / sp.y;
					else
						phi = 0.0;
				}
			}
			phi *= PI / 4.0;

			disk_samples[j].x = r * cos(phi);
			disk_samples[j].y = r * sin(phi);
		}
	}

	void Sampler::map_samples_hemisphere(const float exp)
	{
		int size = samples.size();
		hemisphere_samples.reserve(num_samples * num_sets);

		for (int j = 0; j < size; j++)
		{
			float cos_phi = cos(2.0 * PI* samples[j].x);
			float sin_phi = sin(2.0 * PI * samples[j].x);
			float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
			float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
			float pu = sin_theta * cos_phi;
			float pv = sin_theta * sin_phi;
			float pw = cos_theta;

			hemisphere_samples.push_back(glm::vec3(pu, pv, pw));
		}


	}


}


