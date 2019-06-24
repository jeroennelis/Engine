#include "enpch.h"

// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
	
namespace Engine {
	// ---------------------------------------------------------------- default constructor	

	ViewPlane::ViewPlane(void)
		: hres(400),
		vres(400),
		s(1.0),
		gamma(1.0),
		inv_gamma(1.0),
		show_out_of_gamut(false),
		num_samples(1),
		sampler_ptr(NULL)
	{}


	// ---------------------------------------------------------------- copy constructor

	ViewPlane::ViewPlane(const ViewPlane& vp)
		: hres(vp.hres),
		vres(vp.vres),
		s(vp.s),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		num_samples(vp.num_samples),
		sampler_ptr(vp.sampler_ptr)
	{}


	// ---------------------------------------------------------------- assignment operator

	ViewPlane&
		ViewPlane::operator= (const ViewPlane& rhs) {
		if (this == &rhs)
			return (*this);

		hres = rhs.hres;
		vres = rhs.vres;
		s = rhs.s;
		gamma = rhs.gamma;
		inv_gamma = rhs.inv_gamma;
		show_out_of_gamut = rhs.show_out_of_gamut;

		return (*this);
	}


	// -------------------------------------------------------------- destructor

	ViewPlane::~ViewPlane(void)
	{
		delete sampler_ptr;
	}

	void ViewPlane::set_sampler(Sampler* sampler)
	{
		if (sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}

		num_samples = sampler->get_num_samples();
		sampler_ptr = sampler;
	}

	void ViewPlane::set_samples(const int n)
	{
		num_samples = n;

		if (sampler_ptr)
		{
			delete sampler_ptr;
			sampler_ptr = NULL;
		}

		if (num_samples > 1)
			//sampler_ptr = new MultiJ
			;
		else
			//sampler_ptr = new Regular(1)
			;
	}
}
