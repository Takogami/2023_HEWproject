#include "CWind.h"

CWind::CWind()
{

}

CWind::~CWind()
{

}

void CWind::Update()
{

}

void CWind::Wind_Right(CPlayer* playerStatus, float windPower)
{
	//	右向きベクトル
	playerStatus->dir.x = 1.0f;

	//	風が起きてるような計算
	playerStatus->transform.position.x += playerStatus->dir.x * playerStatus->velocity.x * windPower;
}
