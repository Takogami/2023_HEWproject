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
	//	�E�����x�N�g��
	playerStatus->dir.x = 1.0f;

	//	�����N���Ă�悤�Ȍv�Z
	playerStatus->transform.position.x += playerStatus->dir.x * playerStatus->velocity.x * windPower;
}
