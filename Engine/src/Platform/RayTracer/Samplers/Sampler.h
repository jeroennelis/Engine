#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

namespace Engine {
	class Sampler
	{
	public:
		Sampler();
		Sampler(const int numSamples);
		Sampler(const int numSamples, const int numSets);
		Sampler(const Sampler& s);
		~Sampler();

		virtual void generate_samples(void) = 0;	// generate sample patterns in a unit square

		void setup_shuffled_indices(void);		// set up the random shuffled indices

		void shuffle_sampeles(void);			// randomly shuffle the samples in each pattern

		glm::vec2 sample_unit_square(void);		// get next sample on the unit square

		int const get_num_samples(void) const;

	protected:
		int num_samples;						// the number of sample point in a pattern
		int num_sets;							// the number of sample sets stored
		std::vector<glm::vec2> samples;			// sample points on a unit square
		std::vector<int> shuffled_indices;		// the current number of sample points used
		unsigned long count;					// random index jump
		int jump;
	};



	inline int const Sampler::get_num_samples(void) const
	{
		return num_samples;
	}
}
