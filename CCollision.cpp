#include "CCollision.h"
#include <cmath>

void CCollision::CorrectPosition(BoxCollider& obj1, BoxCollider& obj2)
{
	float overlapX = moveObject->Bcol.sizeX / 2 + holdObject->Bcol.sizeX / 2 - std::abs(moveObject->Bcol.centerX - holdObject->Bcol.centerX);
	float overlapY = moveObject->Bcol.sizeY / 2 + holdObject->Bcol.sizeY / 2 - std::abs(moveObject->Bcol.centerY - holdObject->Bcol.centerY);

	if (overlapX < overlapY)
	{
		// X軸方向にめり込んでいる場合
		if (moveObject->Bcol.centerX < holdObject->Bcol.centerX)
		{
			moveObject->Bcol.centerX -= overlapX;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
		else
		{
			moveObject->Bcol.centerX += overlapX;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.x = moveObject->Bcol.centerX;
		}
	}
	else {
		// Y軸方向にめり込んでいる場合
		if (moveObject->Bcol.centerY < holdObject->Bcol.centerY)
		{
			moveObject->Bcol.centerY -= overlapY;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}
		else
		{
			moveObject->Bcol.centerY += overlapY;
			//コライダーの中心点とオブジェクトの中心点を連動させる
			moveObject->transform.position.y = moveObject->Bcol.centerY;
		}

		//コライダーの中心点とオブジェクトの中心点を連動させる
		moveObject->transform.position.x = moveObject->Bcol.centerX;
		moveObject->transform.position.y = moveObject->Bcol.centerY;
	}
}

bool CCollision::TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2)
{
	// 中心点間の距離
	float distanceX = std::abs(obj1.centerX - obj2.centerX);
	float distanceY = std::abs(obj1.centerY - obj2.centerY);

	// 中心点間の距離がそれぞれの矩形の幅と高さの半分を足したものより小さい場合、重なっていると判定
	if (distanceX < (obj1.sizeX / 2 + obj2.sizeX / 2) && distanceY < (obj1.sizeY / 2 + obj2.sizeY / 2))
	{
		return true;
	}

	return false;
}
