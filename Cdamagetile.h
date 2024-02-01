#pragma once
#include"CGameObject.h"

// 前方宣言
class CPlayer;

class Cdamagetile : public CGameObject
{
private:
	float damageAmount = 0.0f;
	float damageknock = 0.0f;

public:
	Cdamagetile(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type = OBJECT_TYPE::DAMEGE_TILE);
	~Cdamagetile()override;

	void knockback(CPlayer* a ,float back);	//プレイヤーがダメージを受けた時にノックバックする処理
	float Getback(CPlayer* a);
};

