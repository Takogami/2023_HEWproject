#include "CCollision.h"
#include <cmath>

CORRECT_DIR CCollision::CorrectPosition(BoxCollider& moveObject, BoxCollider& holdObject)
{
	// x,yそれぞれめり込んでいる長さを計算
	float overlapX = ((moveObject.sizeX / 2) + (holdObject.sizeX / 2)) - std::abs(moveObject.centerX - holdObject.centerX);
	float overlapY = ((moveObject.sizeY / 2) + (holdObject.sizeY / 2)) - std::abs(moveObject.centerY - holdObject.centerY);
	// 補正した方向を格納するCORRECT_DIR型変数
	CORRECT_DIR correct_dir = { 0 };


	// コライダーを補正する
	if (overlapY < overlapX)
	{
		// Y軸方向にめり込んでいる場合
		if (moveObject.centerY < holdObject.centerY)
		{
			moveObject.centerY -= overlapY;
			correct_dir.y = -1;
		}
		else
		{
			moveObject.centerY += overlapY;
			correct_dir.y = 1;
		}

	}
	//本来のめり込み計算の補正と少し違うので0.002分を＋してあげる
	else if ((overlapX + 0.002f) < overlapY) {
		// X軸方向にめり込んでいる場合
		if (moveObject.centerX < holdObject.centerX)
		{
			moveObject.centerX -= overlapX;
			correct_dir.x = -1;
		}
		else if (moveObject.centerX > holdObject.centerX)
		{
			moveObject.centerX += overlapX;
			correct_dir.x = 1;
		}
	}

	 //補正した方向を返す
	return correct_dir;
}

CORRECT_DIR CCollision::CCollision::DtestCorrectPosition(BoxCollider& moveObject, BoxCollider& holdObject)
{
	// x,yそれぞれめり込んでいる長さを計算
	float overlapX = ((moveObject.sizeX / 2) + (holdObject.sizeX / 2)) - std::abs(moveObject.centerX - holdObject.centerX);
	float overlapY = ((moveObject.sizeY / 2) + (holdObject.sizeY / 2)) - std::abs(moveObject.centerY - holdObject.centerY);
	// 補正した方向を格納するCORRECT_DIR型変数
	CORRECT_DIR correct_dir = { 0 };

	bool XRflg = false;
	bool XLflg = false;

	// コライダーを補正する
		// コライダーを補正する
	if (overlapY < overlapX)
	{
		// Y軸方向にめり込んでいる場合
		if (moveObject.centerY < holdObject.centerY)
		{
			moveObject.centerY -= overlapY;
			moveObject.centerX -= 0.2f;
			correct_dir.y = -1;
		}
		else
		{
			moveObject.centerY += overlapY;
			correct_dir.y = 1;
		}

	}
	//本来のめり込み計算の補正と少し違うので0.002分を＋してあげる
	else if ((overlapX + 0.002f) < overlapY) {
		// X軸方向にめり込んでいる場合
		if (moveObject.centerX < holdObject.centerX)
		{
			moveObject.centerX -= overlapX;
			correct_dir.x = -1;
		}
		else if (moveObject.centerX > holdObject.centerX)
		{
			moveObject.centerX += overlapX;
			correct_dir.x = 1;
		}
	}

	//補正した方向を返す
	return correct_dir;
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
