#include "enpch.h"
#include "Matte.h"

namespace Engine {

	Matte::Matte()
	{
	}

	Matte::Matte(Lambertian* ambient, Lambertian* diffuse)
		:m_AmbientBRDF(ambient),
		m_DiffuseBRDF(diffuse)
	{
	}

	Matte::~Matte()
	{
		delete m_AmbientBRDF;
		delete m_DiffuseBRDF;
	}

	void Matte::SetKa(const float ka)
	{
		m_AmbientBRDF->SetKa(ka);
	}

	void Matte::SetKd(const float kd)
	{
		m_DiffuseBRDF->SetKd(kd);
	}

	void Matte::SetCd(Texture_temp* c)
	{
		m_AmbientBRDF->SetCd(c);
		m_DiffuseBRDF->SetCd(c);
	}

}