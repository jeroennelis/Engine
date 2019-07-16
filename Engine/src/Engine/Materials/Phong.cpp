#include "enpch.h"
#include "Phong.h"

namespace Engine {

	Phong::Phong(Lambertian* ambient, Lambertian* diffuse, GlossySpecular* specular)
		:m_AmbientBRDF(ambient),
		m_DiffuseBRDF(diffuse),
		m_SpecularBRDF(specular)
	{
	}
	void Phong::SetKa(const float ka)
	{
		m_AmbientBRDF->SetKa(ka);
	}
	void Phong::SetKd(const float kd)
	{
		m_DiffuseBRDF->SetKd(kd);
	}
	void Phong::SetKs(const float ks)
	{
		m_SpecularBRDF->SetKs(ks);
	}

	void Phong::SetExp(const float exp)
	{
		m_SpecularBRDF->SetExp(exp);
	}

	void Phong::SetCd(Texture* c)
	{
		m_AmbientBRDF->SetCd(c);
		m_DiffuseBRDF->SetCd(c);
		m_SpecularBRDF->SetCs(c);
	}

	float Phong::GetKa()
	{
		return m_AmbientBRDF->GetKd();
	}

	float Phong::GetKd()
	{
		return m_DiffuseBRDF->GetKd();
	}

	float Phong::GetKs()
	{
		return m_SpecularBRDF->GetKs();
	}

	float Phong::GetExp()
	{
		return m_SpecularBRDF->GetExp();
	}

	Texture* Phong::GetCd()
	{
		return m_SpecularBRDF->GetCs();
	}



}
