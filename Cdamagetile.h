#pragma once

#include "CGameObject.h"

// 前方宣言
class CPlayer;

class Cdamagetile : public CGameObject
{
private:
	float damageAmount = 0.0f;
	float damageknock = 0.01f;

public:
	Cdamagetile(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
	~Cdamagetile()override;

	void knockbackR(CPlayer* a , float s);	//プレイヤーがダメージを受けた時にノックバックする処理
	void knockbackL(CPlayer* a , float s);
	float GetknockP() { return damageknock; };
};

