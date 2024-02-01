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


	void knockback(CPlayer* a ,float back);	//プレイヤーがダメージを受けた時にノックバックする処理

	float Getback(CPlayer* a);



};

