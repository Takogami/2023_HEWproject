#include "Cdamagetile.h"
#include "CPlayer.h"

Cdamagetile::Cdamagetile(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
}

Cdamagetile::~Cdamagetile()
{
	CGameObject::~CGameObject();
}

void Cdamagetile::knockbackR(CPlayer* a , float s)
{
	if (a->Ddir.x == -1.0f)
	{
		s -= 0.001f;
		if (damageknock <= 0.0f)
		{
			a->Ddir.x = 0.0f;
			s = 0.0f;
		}
	}
	a->transform.position.x -= s;
}

void Cdamagetile::knockbackL(CPlayer* a , float s)
{
	if (a->Ddir.x == 1.0f)
	{
		s -= 0.001f;
		if (s <= 0.0f)
		{
			a->Ddir.x = 0.0f;
			s = 0.0f;
		}
	}
	a->transform.position.x += s;
}