#pragma once
#include"CGameObject.h"
#include"CCollision.h"

class CPlayer;

class Cdamagetile : public CGameObject
{
private:
	float damageAmount;
	float damageknock;


public:


	void knockback(CPlayer* a ,float back);	//�v���C���[���_���[�W���󂯂����Ƀm�b�N�o�b�N���鏈��

	float Getback(CPlayer* a);



};

