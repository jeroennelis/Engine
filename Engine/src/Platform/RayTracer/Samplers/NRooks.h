#pragma once
#include "Sampler.h"

namespace Engine {

	class NRooks :
		public Sampler
	{
	public:
		NRooks();
		NRooks(const int numSamples);
		NRooks(const int numSamples, int numSets);
		NRooks(const NRooks& nr);
		~NRooks();

	private:
		virtual void generate_samples(void);
		void shuffle_x_coordinates();
		void shuffle_y_coordinates();
	};
}