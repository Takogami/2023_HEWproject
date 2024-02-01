#include "Cdamagetile.h"
#include "CPlayer.h"

Cdamagetile::Cdamagetile(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type) : CGameObject(vb, tex, uv, type)
{
}

Cdamagetile::~Cdamagetile()
{
	CGameObject::~CGameObject();
}

void Cdamagetile::knockback(CPlayer* a, float back)
{
	if (a->dir.x >= 0.0f)
	{
		a->transform.position.x -= a->dir.x * back;
	}
	else if (a->dir.x <= 0.0f)
	{
		a->transform.position.x += a->dir.x * back;
	}
}

float Cdamagetile::Getback(CPlayer* a)
{
	return a->transform.position.x;
}
