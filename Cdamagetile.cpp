#include "Cdamagetile.h"
#include "CPlayer.h"

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
