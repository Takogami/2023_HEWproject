#pragma once

// BoxCollider型の定義
struct BoxCollider
{
	float centerX;	// Boxコライダーの中心点X
	float centerY;	// Boxコライダーの中心点Y
	float sizeX;	// Boxコライダーのx方向の大きさ
	float sizeY;	// Boxコライダーのy方向の大きさ
};

class CCollision
{
public:

	/* メソッド */

	// 四角形同士の当たり判定
	static bool TestBoxCollision(BoxCollider& obj1, BoxCollider& obj2);
	// 位置補正
	static void CorrectPosition(BoxCollider& obj1, BoxCollider& obj2);

};

