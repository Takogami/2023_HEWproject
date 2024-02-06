#pragma once

#include "CGameObject.h"

// �O���錾
class CPlayer;

class Cdamagetile : public CGameObject
{
private:
	float damageAmount = 0.0f;
	float damageknock = 0.01f;

public:
	Cdamagetile(ID3D11Buffer* vb, ID3D11ShaderResourceView* tex, FLOAT_XY uv, OBJECT_TYPE type);
	~Cdamagetile()override;

	void knockbackR(CPlayer* a , float s);	//�v���C���[���_���[�W���󂯂����Ƀm�b�N�o�b�N���鏈��
	void knockbackL(CPlayer* a , float s);
	float GetknockP() { return damageknock; };
};

